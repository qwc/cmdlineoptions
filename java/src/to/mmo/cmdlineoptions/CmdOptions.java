package to.mmo.cmdlineoptions;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;

/**
 * Written by Marcel M. Otte, (c) 2013 For use under the BSD 2-clause License,
 * or in other words: Do what you want with it as long as you leave all
 * copyright notices where they are and don't bother me when you break your pc.
 * :)
 */

public class CmdOptions {

	private static CmdOptions instance;

	private static String optionChar;
	private HashMap<String, CommandLineOption> options;
	private boolean showOptions;
	private boolean combineSwitches;
	private boolean dontQuitOnError;

	private CmdOptions() {
		optionChar = "-";
		this.setSwitchCombination(false);
		this.setShowOptions(false);
		this.setDontQuitOnError(false);
		options = new HashMap<String, CommandLineOption>();
		this.createOption("help")
				.setDescription(
						"Show all possible options and their parameters.")
				.addLongCommand("--help").addCommand("-h").addCommand("-?");
	}

	public static CmdOptions i() {
		if (instance == null) {
			instance = new CmdOptions();
		}
		return instance;
	}

	public void setSwitchCombination(boolean on) {
		this.combineSwitches = on;
	}

	@SuppressWarnings("static-access")
	public void setOptionCharacter(String c) {
		this.optionChar = c;
	}

	public void setDontQuitOnError(boolean set) {
		this.dontQuitOnError = set;
	}

	public void setShowOptions(boolean show) {
		this.showOptions = show;
	}

	public void setHelpGeneration(boolean on) {
		if (!on) {
			options.remove("help");
		}
	}

	public CommandLineOption createOption(String name) {
		CommandLineOption o = new CommandLineOption(name);
		this.options.put(name, o);
		return o;
	}

	public CommandLineOption getBareOption(String name) {
		return options.get(name);
	}

	public String[] get(String name) {
		return getOption(name);
	}

	public String get(String name, int index) {
		String[] values = getOption(name);
		if (values.length > index && index > 0) {
			return values[index];
		}
		return null;
	}

	public String[] getOption(String name) {
		if (options.get(name).getValues().size() > 0)
			return options.get(name).getValues().toArray(new String[0]);
		else if (options.get(name).getDefaultParameter().size() > 0)
			return options.get(name).getDefaultParameter()
					.toArray(new String[0]);
		return null;
	}

	public List<String> getValuesAsList(String name) {
		if (options.get(name).getValues().size() > 0) {
			return options.get(name).getValues();
		}
		return null;
	}

	public Integer[] getOptionAsInt(String name) {
		if (options.get(name).getValues().size() > 0) {
			ArrayList<Integer> list = new ArrayList<Integer>();
			for (String o : options.get(name).getValues()) {
				list.add(Integer.parseInt(o));
			}
			return list.toArray(new Integer[0]);
		} else if (options.get(name).getDefaultParameter().size() > 0) {
			ArrayList<Integer> list = new ArrayList<Integer>();
			for (String o : options.get(name).getDefaultParameter()) {
				list.add(Integer.parseInt(o));
			}
			return list.toArray(new Integer[0]);
		}
		return null;
	}

	public Integer getOptionAsInt(String name, int index) {
		Integer[] array = getOptionAsInt(name);
		if (index >= 0 && index < array.length) {
			return array[index];
		}
		return null;
	}

	public Double[] getOptionAsDouble(String name) {
		if (options.get(name).getValues().size() > 0) {
			ArrayList<Double> list = new ArrayList<Double>();
			for (String o : options.get(name).getValues()) {
				list.add(Double.parseDouble(o));
			}
			return list.toArray(new Double[0]);
		} else if (options.get(name).getDefaultParameter().size() > 0) {
			ArrayList<Double> list = new ArrayList<Double>();
			for (String o : options.get(name).getDefaultParameter()) {
				list.add(Double.parseDouble(o));
			}
			return list.toArray(new Double[0]);
		}
		return null;
	}

	public Double getOptionAsDouble(String name, int index) {
		Double[] array = getOptionAsDouble(name);
		if (index >= 0 && index < array.length) {
			return array[index];
		}
		return null;
	}

	public boolean isSet(String option) {
		return options.get(option).isSet();
	}

	public boolean isSet(String option, String parameter) {
		return this.getValuesAsList(option).contains(parameter);
	}

	public void resetValues() {
		for (CommandLineOption o : options.values()) {
			o.getValues().clear();
		}
	}

	public void reset() {
		options.clear();
	}

	public String toString(boolean help) {
		StringBuilder b = new StringBuilder();
		if (help) {
			b.append("Possible options:\n");
		}
		b.append("-options\n");
		CommandLineOption[] vars = options.values().toArray(
				new CommandLineOption[0]);
		Arrays.sort(vars, new Comparator<CommandLineOption>() {
			@Override
			public int compare(CommandLineOption o1, CommandLineOption o2) {
				return o1.getName().compareTo(o2.getName());
			}
		});
		for (CommandLineOption o : vars) {
			b.append("\t").append(o.toString(help)).append("\n");
		}
		b.append("/options\n");
		return b.toString();
	}

	private Integer[] getIndices(String[] args) {
		List<Integer> indices = new ArrayList<Integer>();
		for (int i = 0; i < args.length; ++i) {
			if (args[i].startsWith(optionChar)) {
				indices.add(i);
			}
		}
		return indices.toArray(new Integer[0]);
	}

	private CommandLineOption getOptionByCommand(String cmd) {
		for (CommandLineOption o : this.options.values()) {
			for (String s : o.getCmd()) {
				if (cmd.equals(s)) {
					return o;
				}
			}
			for (String s : o.getCmdLong()) {
				if (cmd.equals(s)) {
					return o;
				}
			}
		}
		return null;
	}

	private boolean cmdExists(String cmd) {
		return getOptionByCommand(cmd) != null;
	}

	private boolean switchExists(char c) {
		for (CommandLineOption op : this.options.values()) {
			for (String s : op.getCmd()) {
				if (s.toCharArray()[0] == c) {
					return true;
				}
			}
		}
		return false;
	}

	private CommandLineOption[] getOptionBySwitches(String switches) {
		List<CommandLineOption> o = new ArrayList<CommandLineOption>();
		for (CommandLineOption op : this.options.values()) {
			for (String s : op.getCmd()) {
				for (char c : switches.toCharArray()) {
					if (s.toCharArray()[0] == c) {
						o.add(op);
					}
				}
			}
		}
		return o.toArray(new CommandLineOption[0]);
	}

	public int parse(String[] args) {
		int exit = 0;
		// get indices
		Integer[] indices = getIndices(args);
		// check for correct options
		boolean ok = true;
		for (Integer i : indices) {
			String o = args[i].replace(optionChar, "");
			if (!cmdExists(o)) {
				if (this.combineSwitches) {
					for (char c : o.toCharArray()) {
						if (!switchExists(c)) {
							System.err.println("Unrecognized switch '" + c
									+ "'");
							ok = false;
						}
					}
				} else {
					System.err.println("Unrecognized option '" + o + "'");
					ok = false;
				}
			}
		}
		// quit if there are unknown options
		if (!ok && exit == 0) {
			exit = 1;
		}
		// now parse
		CommandLineOption op;
		for (int a = 0; a < indices.length; ++a) {
			String o = args[indices[a]].replace(optionChar, "");
			op = this.getOptionByCommand(o);
			if (op == null) {
				if (this.combineSwitches) {
					CommandLineOption[] mop = getOptionBySwitches(o);
					for (CommandLineOption opt : mop) {
						opt.setSet(true);
					}
				}
				continue;
			}
			// the option is set!
			op.setSet(true);
			// are there parameters?
			if (indices[a] < args.length - 1 && a < indices.length - 1
					&& indices[a + 1] - indices[a] > 1) {
				// parameters between options
				for (int b = indices[a] + 1; b < indices[a + 1]; ++b) {
					op.getValues().add(args[b]);
				}
			} else if (a == indices.length - 1 && args.length - 1 > indices[a]) {
				// parameters at the last option
				for (int b = indices[a] + 1; b < args.length; ++b) {
					op.getValues().add(args[b]);
				}
			}
		}

		// check for possible parameters
		for (CommandLineOption o : options.values()) {
			for (String s : o.getValues()) {
				if (o.getPossibleParams().size() > 0
						&& !o.getPossibleParams().contains(s)) {
					System.err.println("Parameter \"" + s + "\" for Option \""
							+ o.getName() + "\" not allowed!");
					ok = false;
				}
			}
		}
		if (!ok && exit == 0) {
			exit = 2;
		}

		// check parameter counts
		for (CommandLineOption o : options.values()) {
			if (o.getValues().size() < o.getMinParameters()
					&& o.getMinParameters() != 0
					|| o.getValues().size() > o.getMaxParameters()
					&& o.getMaxParameters() != 0
					|| o.getStepSizeParameters() != 0
					&& o.getValues().size() % o.getStepSizeParameters() != 0) {
				System.err.println(o.getName()
						+ ": Parameter count not correct! Check help.");
				exit = 3;
			}
		}

		// set default for that options that aren't set
		for (CommandLineOption o : options.values()) {
			if (!o.isSet() && o.isRequired()) {
				System.err
						.println(o.getName()
								+ " ("
								+ o.getName()
								+ "): has no default parameter and has to be set on commandline!");
				exit = 4;
			}
			if (!o.isSet() && o.getDefaultParameter().size() != 0)
				o.getValues().addAll(o.getDefaultParameter());
		}
		if (options.get("help").isSet() || exit > 0) {
			System.out.println(this.toString(true));
			if (!this.dontQuitOnError)
				System.exit(exit);
		}
		if (this.showOptions) {
			System.out.println(this.toString(false));
		}
		return exit;
	}

	public static String getOptionChar() {
		return optionChar;
	}
}
