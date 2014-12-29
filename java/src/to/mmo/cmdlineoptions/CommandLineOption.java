package to.mmo.cmdlineoptions;

import java.util.ArrayList;

public class CommandLineOption {
	private String name;
	private ArrayList<String> cmd;
	private ArrayList<String> cmdLong;
	private String description;
	private ArrayList<String> defaultParameter;

	private ArrayList<String> possibleParams;
	private boolean set;
	private boolean required;
	private ArrayList<String> values;
	private int maxParameters, minParameters;
	private ArrayList<String> examples;
	private int stepSizeParameters;

	public CommandLineOption() {
		values = new ArrayList<String>();
		cmd = new ArrayList<String>();
		cmdLong = new ArrayList<String>();
		defaultParameter = new ArrayList<String>();
		possibleParams = new ArrayList<String>();
		examples = new ArrayList<String>();
	}

	public CommandLineOption(String name) {
		this();
		this.name = name;
	}

	public ArrayList<String> getValues() {
		return values;
	}

	public ArrayList<String> getDefaultParameter() {
		return defaultParameter;
	}

	public CommandLineOption addCommand(String cmd) {
		if (cmd.contains(CmdOptions.getOptionChar())) {
			cmd = cmd.replace(CmdOptions.getOptionChar(), "");
		}
		if (cmd.length() > 1) {
			throw new IllegalArgumentException(
					"Command longer than 1 character, which is not allowed. Use 'addLongCommand()' instead!");
		}
		this.cmd.add(cmd);
		return this;
	}

	public CommandLineOption addLongCommand(String cmd) {
		if (cmd.contains(CmdOptions.getOptionChar()))
			cmd = cmd.replace(CmdOptions.getOptionChar(), "");
		this.cmdLong.add(cmd);
		return this;
	}

	public CommandLineOption addDefaultParameter(String d) {
		this.defaultParameter.add(d);
		return this;
	}

	public CommandLineOption addPossibleParameter(String p) {
		this.possibleParams.add(p);
		return this;
	}

	public CommandLineOption addValue(String value) {
		this.values.add(value);
		return this;
	}

	public String getName() {
		return name;
	}

	public CommandLineOption setName(String name) {
		this.name = name;
		return this;
	}

	public CommandLineOption setParameterCount(int min, int max) {
		return this.setParameterCount(min, max, 0);
	}

	public CommandLineOption setParameterCount(int min, int max, int step) {
		this.minParameters = min;
		this.maxParameters = max;
		this.stepSizeParameters = step;
		return this;
	}

	public String getDescription() {
		return description;
	}

	public CommandLineOption setDescription(String description) {
		this.description = description;
		return this;
	}

	public CommandLineOption setRequired(boolean required) {
		this.required = true;
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

	public CommandLineOption setSet(boolean set) {
		this.set = set;
		return this;
	}

	public CommandLineOption addExample(String example) {
		this.examples.add(example);
		return this;
	}

	public String toString() {
		return toString(false);
	}

	public String toString(boolean help) {
		String ret = name;
		ret += " (";
		for (String s : cmd) {
			ret += CmdOptions.getOptionChar() + s + ", ";
		}
		for (String s : cmdLong) {
			ret += CmdOptions.getOptionChar() + CmdOptions.getOptionChar() + s
					+ ", ";
		}
		ret += ")";
		if (help && defaultParameter.size() > 0) {
			ret += ": default=";
			for (String s : defaultParameter) {
				ret += s + ",";
			}
		}
		ret += (help && description != null ? "\n\t\t" + description : "");
		if (help && possibleParams.size() > 0) {
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

	public int getMaxParameters() {
		return maxParameters;
	}

	public void setMaxParameters(int maxParameters) {
		this.maxParameters = maxParameters;
	}

	public int getMinParameters() {
		return minParameters;
	}

	public void setMinParameters(int minParameters) {
		this.minParameters = minParameters;
	}

	public boolean isRequired() {
		return required;
	}

	public int getStepSizeParameters() {
		return stepSizeParameters;
	}

	public void setStepSizeParameters(int stepSizeParameters) {
		this.stepSizeParameters = stepSizeParameters;
	}

	public ArrayList<String> getCmd() {
		return cmd;
	}

	public ArrayList<String> getCmdLong() {
		return cmdLong;
	}

	public ArrayList<String> getPossibleParams() {
		return possibleParams;
	}

	public ArrayList<String> getExamples() {
		return examples;
	}
}
