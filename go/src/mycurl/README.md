
```bash
# tree
.
└── README.md

0 directories, 1 file
# cobra init --pkg-name mycurl
Your Cobra applicaton is ready at
/home/lyre/workspace/misc/go/src/mycurl
# tree
.
├── cmd
│   └── root.go
├── LICENSE
├── main.go
└── README.md

1 directory, 4 files
# cobra add get
get created at /home/lyre/workspace/misc/go/src/mycurl
# tree
.
├── cmd
│   ├── get.go
│   └── root.go
├── LICENSE
├── main.go
└── README.md

1 directory, 5 files
# cobra add post
# cobra add delete
# cobra add put
# cobra add patch

# cobra add info
# cobra add version -p infoCmd
# cobra add aurthor -p infoCmd
```