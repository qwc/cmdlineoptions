package to.mmo.cmdlineoptions.examples;

import to.mmo.cmdlineoptions.CmdOptions;

public class Example {

	public static void initOptions() {
		CmdOptions.i().createOption("name").// give the option a name which you
											// can
											// remember within your project
				addCommand("--name") // it's always good to define a long
										// commandline parameter with a
										// describing name

				.addCommand("-n") // of course, programmer are always lazy so
									// give them an possibility to shortcut your
									// option
				.addDefaultParameter("whatever")// a default parameter is good
												// if you need the option within
												// your program, but don't care
												// when it's omitted on
												// execution
				.setDescription("an example option.");// And of course a
														// description... for
														// the help readers, the
														// few among us...
		CmdOptions
				.i()
				.createOption("name")
				.addCommand("--complex")
				// see above
				// yes you can omit a default parameter, but you have to
				// check later in your project if that option is set.
				.addCommand("-c")
				.setDescription("a complex commandline parameter")
				.addPossibleParameter("something")
				// here the fun begins, you can set as much possible parameters
				// as you want, keep in mind to leave out whitespaces!
				// and remember that you limit your option to exactly that
				// parameters!
				.addPossibleParameter("another_something")
				// here you are able to add some more alternatives for that
				// option, so here you can use "--complex", "-c", "-i" and
				// "--ccp" to trigger this option.
				.addCommand("-i").addCommand("--ccp");

	}

	public static void main(String[] args) {
		initOptions(); // init the commandline options
		CmdOptions.i().parse(args); // parse them, and your done. --help is
									// automatically set, so you can use it
									// right away.

		// now your program follows, using this options...

	}

}
