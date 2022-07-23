# Lister
A console-based checklist

![](https://catmanl.github.io/lister/ss1.png)

Check the
[website](https://catmanl.github.io/lister/index.html)

## Compiling
```console
$ git clone https://github.com/catmanl/lister.git
$ go build -o lister lister.go
```

## A bit more about the lister-specific file format
The first line must be the event's title.

The other lines will be your names.

You can have three states for your names:

- Not checked: no prefix on the name
- To be determined: ? prefix on the name
- Checked: x prefix on the name

![](https://catmanl.github.io/lister/ss3.png)
![](https://catmanl.github.io/lister/ss2.png)

## License
Lister is licensed under the GPL 2.0 license.
