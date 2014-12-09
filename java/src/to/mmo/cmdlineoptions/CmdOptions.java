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

	public static class Option {
		private String name;
		private ArrayList<String> cmd;
		private String description;
		private ArrayList<String> defaultParameter;

		private ArrayList<String> possibleParams;
		private boolean set;
		private ArrayList<String> values;

		public ArrayList<String> getValues() {
			return values;
		}

		public ArrayList<String> getDefaultParameter() {
			return defaultParameter;
		}

		public Option() {
			values = new ArrayList<String>();
			cmd = new ArrayList<String>();
			defaultParameter = new ArrayList<String>();
			possibleParams = new ArrayList<String>();
		}

		public Option addCommand(String cmd) {
			this.cmd.add(cmd);
			return this;
		}

		public Option addDefaultParameter(String d) {
			this.defaultParameter.add(d);
			return this;
		}

		public Option addPossibleParameter(String p) {
			this.possibleParams.add(p);
			return this;
		}

		public Option addValue(String value) {
			this.values.add(value);
			return this;
		}

		public String getName() {
			return name;
		}

		public Option setName(String name) {
			this.name = name;
			return this;
		}

		public String getDescription() {
			return description;
		}

		public Option setDescription(String description) {
			this.description = description;
			return this;
		}

		public boolean isSet() {
			return set;
		}

		public boolean valuesContains(String value) {
			return values.contains(value);
		}

		public int getIndexOf(String value) {
			return values.indexOf(value);
		}

		public Option setSet(boolean set) {
			this.set = set;
			return this;
		}

		public String toString() {
			String ret = name + " (";
			for (String s : cmd) {
				ret += s + ", ";
			}
			ret += ")"
					+ (defaultParameter != null ? ": default="
							+ defaultParameter : "")
					+ (description != null ? "\n\t\t" + description : "");
			if (possibleParams != null) {
				boolean start = true;
				ret += "\n\t\t(Possible parameters: ";
				for (String s : possibleParams) {
					ret += (start ? "" : ", ") + s;
					start = false;
				}
				ret += ")";
			}
			if (set) {
				ret += "\n\t\t--> current Setting: ";
				if (values.size() > 0) {
					boolean start = true;
					for (String s : values) {
						ret += (start ? "" : ",") + s;
						start = false;
					}
				} else {
					ret += "true";
				}
				// ret += "\n";
			}
			return ret;
		}
	}

	private HashMap<String, Option> options;

	private CmdOptions() {
		options = new HashMap<String, Option>();
		this.createOption("help")
				.setDescription(
						"Show all possible options and their parameters.")
				.addCommand("--help").addCommand("-h").addCommand("-?");
	}

	public static CmdOptions i() {
		if (instance == null) {
			instance = new CmdOptions();
		}
		return instance;
	}

	public Option createOption(String name) {
		Option o = new Option();
		o.setName(name);
		this.options.put(name, o);
		return o;
	}

	public String[] get(String name) {
		return getOption(name);
	}

	public String[] getOption(String name) {
		if (options.get(name).values.size() > 0)
			return options.get(name).values.toArray(new String[0]);
		else if (options.get(name).defaultParameter != null)
			return options.get(name).getValues().toArray(new String[0]);
		return null;
	}

	public List<String> getValuesAsList(String name) {
		if (options.get(name).getValues().size() > 0) {
			return options.get(name).getValues();
		}
		return null;
	}

	public Integer[] getOptionAsInt(String name) {
		if (options.get(name).values.size() > 0) {
			ArrayList<Integer> list = new ArrayList<Integer>();
			for (String o : options.get(name).values) {
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

	public Double[] getOptionAsDouble(String name) {
		if (options.get(name).values.size() > 0) {
			ArrayList<Double> list = new ArrayList<Double>();
			for (String o : options.get(name).values) {
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

	public boolean isSet(String option) {
		return options.get(option).set;
	}

	public boolean isSet(String option, String parameter) {
		for (String o : options.get(option).values) {
			if (o.equals(parameter)) {
				return true;
			}
		}
		return false;
	}

	public String toString(boolean help) {
		StringBuilder b = new StringBuilder();
		if (help) {
			b.append("Possible options:\n");
		}
		b.append("-options\n");
		Option[] vars = options.values().toArray(new Option[0]);
		Arrays.sort(vars, new Comparator<Option>() {
			@Override
			public int compare(Option o1, Option o2) {
				return o1.name.compareTo(o2.name);
			}
		});
		for (Option o : vars) {
			b.append("\t").append(o.toString()).append("\n");
		}
		b.append("/options\n");
		return b.toString();
	}

	public void parse(String[] args) {
		// now parse
		if (args.length > 0) {
			int i = 0;
			String arg = null;
			// iterate through all options
			for (; i < args.length; ++i) {
				arg = args[i];
				Option o = null;
				// search for correct option
				for (Option op : options.values()) {
					for (String s : op.cmd)
						if (arg.equals(s)) {
							o = op;
							break;
						}
				}
				// if it is unknown
				if (o == null) {
					System.err.println("Unrecognized option '" + arg + "'");
					continue;
				}
				o.set = true;
				// now iterate through the parameters
				int j = i + 1;
				while (args.length > j && !args[j].startsWith("-")) {
					if (o.possibleParams.size() > 0) {
						if (o.possibleParams.contains(args[j]))
							o.values.add(args[j]);
						else
							System.err.println("Parameter \"" + args[j]
									+ "\" for Option \"" + o.name
									+ "\" not allowed!");
					} else {
						o.values.add(args[j]);
					}
					++j;
				}
				i = j - 1;
			}
		}
		if (options.get("help").set) {
			System.out.println(this.toString(true));
			System.exit(0);
		}

		// set default for that options that aren't set
		for (Option o : options.values()) {
			if (!o.set && o.defaultParameter != null
					&& o.defaultParameter.equals("")) {
				System.err
						.println(o.name
								+ " ("
								+ o.getName()
								+ "): has no default parameter and has to be set on commandline!");
				System.exit(1);
			}
			if (!o.set && o.defaultParameter != null)
				o.values.addAll(o.defaultParameter);
		}
		System.out.println(this.toString(false));
	}
}
