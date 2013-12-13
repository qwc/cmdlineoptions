package to.mmo.cmdlineoptions.examples;

import to.mmo.cmdlineoptions.CmdOptions;

public class Example {

	public static void initOptions() {
		CmdOptions.i().setOption("name", // give the option a name which you can
											// remember within your project
				"--name", // it's always good to define a long commandline
							// parameter with a describing name
				"-n", // of course, programmer are always lazy so give them an
						// option to shortcut your option
				"whatever", // a default parameter is good if you need the
							// option within your program, but don't care when
							// it's omitted on execution
				"an example option"); // And of course a description... for the
										// help readers, the few among us...
		CmdOptions.i().setOption(
				"complex", // see above
				"--complex", "-c",
				null, // yes you can omit a default parameter, but you have to
						// check later in your project if that option is set.
				"a complex commandline parameter",
				new String[] { "something", "another_something" },
				// here the fun begins, you can set as much possible parameters
				// as you want, keep in mind to leave out whitespaces!
				// and remember that you limit your option to exactly that
				// parameters!
				new String[] { "-i", "--ccp" });
		// here you are able to add some more alternatives for that option, so
		// here you can use "--complex", "-c", "-i" and "--ccp" to trigger this
		// option.

	}

	public static void main(String[] args) {
		initOptions(); // init the commandline options
		CmdOptions.i().parse(args); // parse them, and your done. --help is automatically set, so you can use it right away.
		
		// now your program follows using this options...

	}

}
