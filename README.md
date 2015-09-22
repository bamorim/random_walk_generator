# Random Walk Generator

This simulator generates a graph based on the current state of a random walk on the graph.

## Compiling

To compile, simply use the `make` command.

## Running

For running you can use the generated binary on `./bin/simulator`. To see all the options use the `./bin/simulator --help` command.

```
$ ./bin/simulator --help
Usage:
  ./bin/simulator [OPTION...]

    -h, --help  prints the help message

     params options:

       -s, --steps arg          steps taken on each addition (default:1)
    -r, --seed arg           defaults to random
      -v, --max-order arg      [required] desired order (||V||)
    -k, --initial-order arg  order of the complete starting graph (default:3)
```

## Testing

This projects use the awesome header-only test library [Catch][catch]. I've also created a shell script that makes things simpler. So you have 3 ways of testing:

### Test all

You can just use the `make test` to build the tests and run all tests

### Specific tests

Alternatively, you can use `make bin/test` to generate the test binary and can use the executable to more usages.

Typing `./bin/test --help` you can see all the options for using the binary (This can also be seem in the [Catch documentation][catch_doc]).

If you don't want to build and use the test binary every time, you can use the `run_tests` script, which basically calls `make bin/test` and proxies the arguments to `./bin/test`.

So typing `./run_tests [graph]` is the same as running `make bin/test; ./bin/test [graph]`, but a little bit simpler.

Ah, and the command above run the tests tagged with the `[graph]` tag.

Again, check everything on the [Catch documentation][catch_doc]

## Additional libraries

As mentioned above, this project uses [Catch][catch] library for tests. But it also uses the [cxxopts][cxxopts] header-only library for parsing program options, which is simple, based on Boost's counterpart, but way less bloated. Simplicity is king.

[catch]: https://github.com/philsquared/Catch "Catch"
[catch_doc]: https://github.com/philsquared/Catch/blob/master/docs/Readme.md "Catch Documentation"
[cxxopts]: https://github.com/jarro2783/cxxopts
