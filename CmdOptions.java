package at.mkw.inlocs.blinksetassembler.server;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;

public class CmdOptions {

  private static CmdOptions instance;

  public static class Option {
    public String name;
    public String cmdOption;
    public String longCmdOption;
    public String description;
    public String defaultParameter;
    public String[] possibleParams;
    public String[] alternatives;
    public boolean set;
    public ArrayList<String> values;

    public Option() {
      values = new ArrayList<String>();
    }

    public String toString() {
      String ret = name + " (" + longCmdOption + (cmdOption != null ? "/" + cmdOption : "") + ")"
          + (defaultParameter != null ? ": default=" + defaultParameter : "") + (description != null ? "\n\t\t" + description : "");
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
    this.setOption("help", "--help", "-h", null, "Show all possible options and their parameters.", null, new String[] { "-?" });
  }

  public static CmdOptions i() {
    if (instance == null) {
      instance = new CmdOptions();
    }
    return instance;
  }

  public String[] getOption(String name) {
    if (options.get(name).values.size() > 0)
      return options.get(name).values.toArray(new String[0]);
    else if (options.get(name).defaultParameter != null)
      return new String[] { options.get(name).defaultParameter };
    return null;
  }

  public Integer[] getOptionAsInt(String name) {
    if (options.get(name).values.size() > 0) {
      ArrayList<Integer> list = new ArrayList<Integer>();
      for (String o : options.get(name).values) {
        list.add(Integer.parseInt(o));
      }
      return list.toArray(new Integer[0]);
    } else if (options.get(name).defaultParameter != null)
      return new Integer[] { Integer.parseInt(options.get(name).defaultParameter) };
    return null;
  }

  public Double[] getOptionAsDouble(String name) {
    if (options.get(name).values.size() > 0) {
      ArrayList<Double> list = new ArrayList<Double>();
      for (String o : options.get(name).values) {
        list.add(Double.parseDouble(o));
      }
      return list.toArray(new Double[0]);
    } else if (options.get(name).defaultParameter != null)
      return new Double[] { Double.parseDouble(options.get(name).defaultParameter) };
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

  public void setOption(String name, String longcmd, String cmd, String defaultparam, String description) {
    this.setOption(name, longcmd, cmd, defaultparam, description, null, null);
  }

  public void setOption(String name, String longcmd, String cmd, String defaultparam, String description, String[] possibleParams, String[] alternatives) {
    Option o = new Option();
    o.cmdOption = cmd;
    o.name = name;
    o.longCmdOption = longcmd;
    o.defaultParameter = defaultparam;
    o.description = description;
    o.alternatives = alternatives;
    o.possibleParams = possibleParams;
    options.put(name, o);
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
      int l = 0, i = 0;
      String arg = null;
      // iterate through all options
      for (; i < args.length; ++i) {
        arg = args[i];
        Option o = null;
        // search for correct option
        for (Option op : options.values()) {
          if (arg.equals(op.longCmdOption) || op.cmdOption != null && arg.equals(op.cmdOption) || op.alternatives != null
              && Arrays.asList(op.alternatives).contains(arg)) {
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
          if (o.possibleParams != null) {
            if (Arrays.asList(o.possibleParams).contains(args[j]))
              o.values.add(args[j]);
            else
              System.err.println("Parameter \"" + args[j] + "\" for Option \"" + o.name + "\" not allowed!");
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
      if (!o.set && o.defaultParameter != null && o.defaultParameter.equals("")) {
        System.err.println(o.name + " (" + o.cmdOption + "): has no default parameter and has to be set on commandline!");
        System.exit(1);
      }
      if (!o.set && o.defaultParameter != null)
        o.values.add(o.defaultParameter);
    }
    System.out.println(this.toString(false));
  }
}
