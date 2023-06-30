# Wakeup

Protocol handler for waking up Pear applications. Wakeup intercepts `pear:` links, maps them to an application path, and launches the corresponding application, passing it the link.

## Building

To build Wakeup, start by configuring the build tree:

```sh
cmake -B build
```

Next, perform a build:

```sh
cmake --build build
```

Finally, install the application bundle somewhere:

```sh
cmake --install build --prefix <path>
```

`<path>` should be chosen based on your system, such as `/Applications` on macOS or `C:\Program Files` on Windows. The `install/` directory in the root of the repository may also be used.

## License

Apache-2.0
