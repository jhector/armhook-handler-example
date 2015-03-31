# Handler example for armhook
This should give an idea about how to configure and write the hook handler.

# Getting the code
When you initialize the repo as described over at the [armhook](https://github.com/jhector/armhook) README, instead of using the default manifest, use the manifset included in this repository. You can do so by running this init command:
```
$ repo init -u https://github.com/jhector/armhook-handler-example.git -m manifest.xml
```

# Building executable and library
A sample target binary is included, it is implemented in `target.c`, the code for the handler library is in `handler.c`.
As I mentioned before, so far I have only tested everything using the flame device running FirefoxOS.

## flame
Follow the instructions given in the [armhook](https://github.com/jhector/armhook) repository. Once `armhook` and `libarmhook.so` have been build and pushed to the device, you can then build the example target and the handler by running the `build.sh` script inside the B2G directory as follows:
```
$ ./build.sh example_target
$ ./build.sh libhandler
```

After a successful build, you can push those onto the device as well. At last you will push the `config.json` file in this repository to the device as well.

# Running the example
You can use the command `adb shell` to get a shell on the device, I would suggest you do it with two terminals.
Run
```
$ /path/to/example_target
```
The output will look something like this:
```
$ /path/to/example_target
pid: 29905
&value: 0xbefa0a9c
&get_value: 0xb6f09475
value: 0x1e118368
```
At this point the application is waiting for the user to press enter, after he does so, it will print another random value. Now let's try the hooking. Run the application once more but wait before you press enter.

## Setting the hooks
We want to hook the `get_value` function of the given target, when you look at the `config.json` you see that we hook an offset relative to the base of `example_target`, this offset should be right at the `get_value` function, you can check the offset by using the values printed by the application and `/proc/<pid>/maps`. The offset shouldn't change, but in case it doesn't work, this could be the reason.

You may also need to adjust the string that says "/data/libhandler.so" to the actual path where you put the handler library. Do the same thing with the "/data/libarmhook.so" path if you haven't put the helper library into the /data/ directory.

Ok, once everything is configure you are ready to hook the function. Run this command with given pid by the application (use the second connection):
```
root@flame:/ # /path/to/armhook /path/to/config.json <pid>
```

If you see something like this in your output than everything worked:
```
INFO [system/armhook/core/Process.cpp:698] address: 0xb6fe0475 hooked with detour handler: handler_get_value
DEBUG [system/armhook/core/Process.cpp:705] cache cleared for hook
```

When you switch back to the terminal where you started the application, and press enter (and the hooking worked) the output will show this:
```
value: 0xdeadbeef
$
```

Congratulations we successfully hooked the function. Go have fun.
