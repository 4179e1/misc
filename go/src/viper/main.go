package main

/*
	usage:
	  - go run main.go --client.foo=baz
	  - MYAPP_CLIENT_FOO=baz MYAPP_CLIENT_ECHO=0 go run main.go
	  - go run main.go --config <path to config>
*/

import (
	"fmt"
	"net/url"
	"path/filepath"
	"strings"
	"time"

	"github.com/fsnotify/fsnotify"
	"github.com/spf13/pflag"
	"github.com/spf13/viper"
	_ "github.com/spf13/viper/remote" // enabble viper remote config
)

var globalSource = pflag.String("global.source", "default(flag)", "identify the source of configuration")

//var globalUnset = pflag.String("global.unset", "default(flag)", "this parameter do not appear in config file")
var globalUnset = pflag.String("global.unset", "", "this parameter do not appear in config file")
var serverAddress = pflag.String("server.address", "", "server listen address, empty for all")
var serverPort = pflag.Int("server.port", 8080, "server listen port")

/*
	configVar 采用了另一种方式来初始化
	主要是为了强调这个命令行参数的特殊性，这个参数是需要在代码中直接引用的
	其他参数是跟viper绑定的，不会直接使用，而是通过viper.GetType()来获取

	另外一个原因是，plfag.String()返回的是*string，用起来没那么直观
*/
var configVar string

func init() {
	pflag.StringVar(&configVar, "config", "", "config file path")
}

func setRemoteConfig(u *url.URL) {
	/*
		这里接受etcd 或 consul 的url

		etcd:
		  url格式为： etcd+http://127.0.0.1:2380/path/to/key.yaml
		  其中：provider=etcd, endpoint=http://127.0,0.1:2380, path=/path/to/key

		consul:
		  url格式为：consul://127.0.0.1:8500/key.json
		  其中：provider=consul, endpoint=127.0,0.1:8500, path=key.json

		TODO: consul 的 key name 可以包含 . 吗？
	*/

	var provider string
	var endpoint string
	var path string

	schemes := strings.SplitN(u.Scheme, "+", 2)
	if len(schemes) < 1 {
		panic(fmt.Errorf("invalid config scheme '%s'", u.Scheme))
	}

	provider = schemes[0]
	switch provider {

	case "etcd":
		if len(schemes) < 2 {
			panic(fmt.Errorf("invalid config scheme '%s'", u.Scheme))
		}
		protocol := schemes[1]
		endpoint = fmt.Sprintf("%s://%s", protocol, u.Host)
		path = u.Path
	case "consul":
		endpoint = u.Host
		path = u.Path[1:]
	default:
		panic(fmt.Errorf("unsupported provider '%s'", provider))
	}

	//  配置文件的后缀
	ext := filepath.Ext(path)
	if ext == "" {
		panic(fmt.Errorf("Using remote config, without specifiing file extension"))
	}
	// .yaml ==> yaml
	configType := ext[1:]

	fmt.Printf("Using Remote Config Provider: '%s', Endpoint: '%s', Path: '%s', ConfigType: '%s'\n", provider, endpoint, path, configType)
	if err := viper.AddRemoteProvider(provider, endpoint, path); err != nil {
		panic(fmt.Errorf("error adding remote provider %s", err))
	}

	viper.SetConfigType(configType)
}

func setDefaultValue() {

	viper.SetDefault("global.unset", "default(viper)")
	/* add more */
}

func watchRemoteConf() {
	for {
		time.Sleep(time.Second * 5) // delay after each request

		// currently, only tested with etcd support
		err := viper.WatchRemoteConfig()
		if err != nil {
			fmt.Printf("unable to read remote config: %v\n", err)
			continue
		}

		// unmarshal new config into our runtime config struct. you can also use channel
		// to implement a signal to notify the system of the changes
		//runtime_viper.Unmarshal(&runtime_conf)
		fmt.Println("Watching Remote Config")
		fmt.Printf("Global.Source: '%s'\n", viper.GetString("Global.Source"))
		fmt.Printf("Global.ChangeMe: '%s'\n", viper.GetString("Global.ChangeMe"))
	}
}

func main() {

	// 假设--config参数指向本地文件
	isRemoteConfig := false

	pflag.Parse()
	/*
		viper.BindPFlags 自动绑定了所有命令行参数，如果只需要其中一部分，可以用viper.BingPflag选择性绑定，如
		viper.BindPFlag("global.source", pflag.Lookup("global.source"))
	*/
	viper.BindPFlags(pflag.CommandLine)
	setDefaultValue()

	// read from env
	viper.AutomaticEnv()
	// so that client.foo maps to MYAPP_CLIENT_FOO
	viper.SetEnvPrefix("MYAPP")
	viper.SetEnvKeyReplacer(strings.NewReplacer(".", "_"))

	if configVar != "" {
		/*
			如果设置了--config参数，尝试从这里解析
			它可能是一个Remote Config，来自etcd或consul
			也可能是一个本地文件
		*/
		u, err := url.Parse(configVar)
		if err != nil {
			panic(fmt.Errorf("error parsing: '%s'", configVar))
		}

		if u.Scheme != "" {
			// 看起来是个remote config
			setRemoteConfig(u)
			isRemoteConfig = true
		} else {
			viper.SetConfigFile(configVar)
		}
	} else {
		/*
			尝试搜索若干默认路径，先后顺序如下:
			- /etc/myapp/config.<ext>
			- ~/.myapp/config.<ext>
			- ./config.<ext>

			其中<ext> 是 viper所支持的文件类型，如yml，json等
		*/

		viper.SetConfigName("config") //name of config file (without extension)
		viper.AddConfigPath("/etc/myapp")
		viper.AddConfigPath("$HOME/.myapp/")
		viper.AddConfigPath(".")
	}

	// read from config
	var err error
	if isRemoteConfig {
		err = viper.ReadRemoteConfig()
		if err != nil {
			panic(fmt.Errorf("error reading config: %s", err))
		}
		fmt.Printf("Using Remote Config: '%s'\n", configVar)

		viper.WatchRemoteConfig()

		go watchRemoteConf()

	} else {
		err = viper.ReadInConfig()
		if err != nil {
			panic(fmt.Errorf("error reading config: %s", err))
		}
		fmt.Printf("Using configuration file '%s'\n", viper.ConfigFileUsed())

		viper.WatchConfig()
		viper.OnConfigChange(func(e fsnotify.Event) {
			fmt.Println("Config file changed:", e.Name)
			fmt.Printf("Global.Source: '%s'\n", viper.GetString("Global.Source"))
			fmt.Printf("Global.ChangeMe: '%s'\n", viper.GetString("Global.ChangeMe"))
		})

	}

	// where does it from
	fmt.Printf("Global.Source: '%s'\n", viper.GetString("global.source"))
	fmt.Printf("Global.ChangeMe: '%s'\n", viper.GetString("Global.ChangeMe"))
	// prints 'default(viper)'
	fmt.Printf("viper.GetString(\"Global.Unset\") = '%s'\n", viper.GetString("global.unset"))
	fmt.Printf("Var GlobalUnset = '%s'\n", *globalUnset)

	// from config file
	fmt.Println("client.servers: ", viper.GetStringSlice("client.servers"))
	fmt.Println("Server.Address: ", viper.GetString("Server.Address"))
	// it can be changed... but when to do that?
	viper.Set("Server.Address", "0.0.0.0")
	// case *insensitive*
	fmt.Println("Server.Address: ", viper.GetString("server.address"))

	// from env
	fmt.Println("client.foo:", viper.GetString("client.foo"))
	fmt.Println("client.echo:", viper.GetBool("client.echo"))

	// block for watch test
	time.Sleep(3600 * time.Second)
}
