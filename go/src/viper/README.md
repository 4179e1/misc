# Golang生态：使用viper管理配置

## 配置管理

通过配置，我们可以动态地改变程序的行为，常用的方式包括配置文件，命令行参数，环境变量等。我原来一直很欣赏ssh的配置管理方式:

- 每一个配置项都有一个默认值
- 这些默认值可以在的配置文件(/etc/ssh/ssh_config)中修改
- 每个配置项都可以通过命令行参数临时覆盖

一直以来笔者都希望在自己的项目中实现类似的功能，但是毫无疑问，这些东西做起来是相当费工夫的。在研究Golang周边生态时，我发现了viper（https://github.com/spf13/viper）这个全面的配置解决方案，它提供的比我能想到的还要多：

- 支持多种配置文件格式，包括 JSON,TOML,YAML,HECL,envfile，甚至还包括Java properties
- 支持为配置项设置默认值
- 可以通过命令行参数覆盖指定的配置项
- 支持参数别名
  
viper按照这个优先级（从高到低）获取配置项的取值：

- explicit call to Set: 在代码逻辑中通过viper.Set()直接设置配置项的值
- flag：命令行参数
- env：环境变量
- config：配置文件
- key/value store：etcd或者consul
- default：默认值

下面通过一个myapp（https://github.com/4179e1/misc/tree/master/go/src/viper）的例子来简单介绍这些特性。

## 配置文件

myapp使用一个配置文件，yaml的格式如下：

```yaml
Global:
  Source: "config(local)"
  LogLevel: "info"
  ChangeMe: "v3"

Server:
  Address: "127.0.0.1"
  Port: 8080

Client:
  Echo: true
  Foo: "bar"
  Servers:
    - "127.0.0.1"
    - "192.168.1.1"
```

直接运行./myapp 会尝试从以下路径寻找名为config.**ext**的配置文件

- /etc/maypp/
- ~/.myapp/
- . (当前目录)

其中.**ext**表示配置文件的后缀如yaml，我们甚至不用指定这个后缀，viper会找自己支持的格式。如果想要指定配置文件路径，可以使用./myapp --config /path/to/config.yaml

```go
	if configVar != "" {
			viper.SetConfigFile(configVar)
	} else {
		viper.SetConfigName("config") //name of config file (without extension)
		viper.AddConfigPath("/etc/myapp")
		viper.AddConfigPath("$HOME/.myapp/")
		viper.AddConfigPath(".")
    }
    
    err = viper.ReadInConfig()
	if err != nil {
		panic(fmt.Errorf("error reading config: %s", err))
	}
	fmt.Printf("Using configuration file '%s'\n", viper.ConfigFileUsed())

    fmt.Printf("Global.Source: '%s'\n", viper.GetString("global.source"))
```

这里要执行viper.ReadInConfig()之后，viper.ReadInConfig()才能确定到底用了哪个文件，viper按照上面的ConfigPath搜索，找到第一个名为config.**ext**的文件后即停止。如果有多个名为config的文件，按照以下顺序搜索

- config.json
- config.toml
- config.yaml
- config.yml
- config.properties
- config.props
- config.prop
- config.hcl

运行这个程序可以看到它正确的读取了globla.source的值，并且它是大小写不敏感的

```bash
$ go run main.go
Using configuration file '/Users/lyre/workspace/misc/go/src/viper/config.yaml'
Global.Source: 'config(local)'

$ go run main.go  --config ./config.yaml
Using configuration file './config.yaml'
Global.Source: 'config(local)'
```

## 环境变量

云原生的12要素里面有一条是“在环境中存储配置“， 在配置文件的基础上，我们还可以用环境变量来覆盖，甚至是完全代替配置文件，下面的代码中，viper会自动捕获所有以MYAPP_开头的环境变量，比如Global.Source这个参数映射到了MYAPP_GLOBAL_SOURCE

```go
	viper.AutomaticEnv()
	viper.SetEnvPrefix("MYAPP")
	viper.SetEnvKeyReplacer(strings.NewReplacer(".", "_")
```

尽管配置文件中指定了Global.Source，但是它的值被环境变量覆盖了

```bash
$ MYAPP_GLOBAL_SOURCE=env go run main.go
Using configuration file '/Users/lyre/workspace/misc/go/src/viper/config.yaml'
Global.Source: 'env'
```

`viper.AutomaticEnv()`会绑定所有环境变量，如果只希望绑定特定的，可以使用`SetEnvPrefix("global.source", "MYAPP_GLOAL_SOURCE")`，注意这个函数不会自动加上MYAPP的前缀.

## 命令行参数

viper可以配合pflag来使用，pflag可以理解为标准库flag的一个增强版，viper可以绑定到pflag上

```go
var globalSource = pflag.String("global.source", "default(flag)", "identify the source of configuration")
var serverAddress = pflag.String("server.address", "", "server listen address, empty for all")
var serverPort = pflag.Int("server.port", 8080, "server listen port"

func main() {
    /* ... */
	pflag.Parse()
	viper.BindPFlags(pflag.CommandLine)
    /* ... */
}
```

下面的例子中，虽然配置文件和环境变量都为Global.Source赋了值，但是命令行参数的优先级更高

```bash
$ MYAPP_GLOBAL_SOURCE=env go run main.go --config ./config.yaml --global.source flag
Using configuration file './config.yaml'
Globle.Source: 'flag'
```

`viper.BindPFlags() `自动绑定了所有命令行参数，如果只需要其中一部分，可以用viper.BingPflag()选择性绑定，如`viper.BindPFlag("global.source", pflag.Lookup("global.source"))`

## 默认值

viper支持为配置项设置默认值，如果在配置文件，环境变量，以及命令行参数中都没有设置，则使用默认值。这带来一个小问题，pflag命令行参数也支持默认值，它们组合关系的结果是怎么样的？

```go
var globalUnset = pflag.String("global.unset", "default(flag)", "this parameter do not appear in config file")

func main() {
    pflag.Parse()
	viper.BindPFlags(pflag.CommandLine)
    viper.SetDefault("global.unset", "default(viper)")
    fmt.Println (viper.GetString("global.unset")) // ???
}
```

- `viper.SetDefault()`的优先级更高，只要设置了这个，它会忽略pflag的默认值，除非运行时显式指定了命令行参数的值
- 如果pflag设置了默认值而viper没有，viper取pflag的值

## Remote KV Store

最后，作为对本地配置文件的替代品，viper支持从etcd/consul直接读取配置，以etcd为例：

```go
viper.AddRemoteProvider("etcd", "http://127.0.0.1:4001","/config/hugo.json")
viper.SetConfigType("json") // because there is no file extension in a stream of bytes, supported extensions are "json", "toml", "yaml", "yml", "properties", "props", "prop", "env", "dotenv"
err := viper.ReadRemoteConfig()
```

跟本地配置文件不同的一点在于，这里要显示声明配置文件的格式，因为viper是通过文件流读取的，它不知道mime信息。

在此基础上，我对 --config 参数做了一些扩展，如果它的参数是以下两种形式之一则会从etcd或consul读取配置，而不再使用本地配置文件：

- etcd+http://127.0.0.1:2380/path/to/key.yaml
- consul://127.0.0.1:8500/key.json

```bash
# 往etcd里面写入这个配置
$ ETCDCTL_API=2 etcdctl set /config/myapp/config.yaml <<EOF
Global:
  Source: "etcd"
  LogLevel: "info"
  ChangeMe: "v3"

Server:
  Address: "127.0.0.1"
  Port: 8080

Client:
  Echo: true
  Foo: "bar"
  Servers:
    - "127.0.0.1"
    - "192.168.1.1"
EOF

# 通过viper读取

$ go run main.go --config etcd+http://127.0.0.1:2379/config/myapp/config.yaml
Using Remote Config: 'etcd+http://127.0.0.1:2379/config/myapp/config.yaml'
Global.Source: 'etcd'
```

> - viper 目前只支持etcd v2 api
> - consul不熟，没测试

## Watch机制

viper还有一个重要特性是能够监控配置文件的修改，对于本地文件，是通过ionotify实现的，然后通过一个回调函数去通知应用来reload：

```go
		viper.WatchConfig()
		viper.OnConfigChange(func(e fsnotify.Event) {
			fmt.Println("Config file changed:", e.Name)
		})
```

对于Remote KV Store，目前只支持etcd，但是做法就比较ugly了，居然是用轮询的，没用上watch api
```go
// open a goroutine to watch remote changes forever
go func(){
	for {
	    time.Sleep(time.Second * 5) // delay after each request

	    // currently, only tested with etcd support
	    err := runtime_viper.WatchRemoteConfig()
	    if err != nil {
	        log.Errorf("unable to read remote config: %v", err)
	        continue
	    }

	    // unmarshal new config into our runtime config struct. you can also use channel
	    // to implement a signal to notify the system of the changes
	    runtime_viper.Unmarshal(&runtime_conf)
	}
}()
```

## Bugfix

如果你启用了go mod，在从etcd读取配置的时候可能会遇到这个错误

```raw
panic: codecgen version mismatch: current: 8, need 10. Re-generate file: /Users/lyre/go/pkg/mod/github.com/coreos/etcd@v3.3.10+incompatible/client/keys.generated.go
```

解决办法是：

```bash
go get github.com/ugorji/go@v1.1.1
go get github.com/ugorji/go/codec@none
```

## Links

- viper（https://github.com/spf13/viper）
- myapp（https://github.com/4179e1/misc/tree/master/go/src/viper）