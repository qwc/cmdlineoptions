package to.mmo.cmdlineoptions.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import to.mmo.cmdlineoptions.CmdOptions;

public class Tests {

	@Before
	public void setupCmdOptions() {
		CmdOptions.i().createOption("test").addCommand("t")
				.addLongCommand("test").setParameterCount(0, 1);
		CmdOptions.i().createOption("test2").addCommand("f");
		CmdOptions.i().createOption("complex").addCommand("c")
				.addLongCommand("complex").addDefaultParameter("wtf")
				.addPossibleParameter("wtf").addPossibleParameter("wth");
	}

	@Test
	public void testSingle() {
		CmdOptions.i().setShowOptions(false);
		String argstr = "-t";
		String[] args = argstr.split(" ");
		CmdOptions.i().parse(args);

		assertTrue(CmdOptions.i().isSet("test"));
		// assertEquals("test", CmdOptions.i().get("test")[0]);
	}

	@Test
	public void testSingle2() {
		CmdOptions.i().setShowOptions(false);
		String argstr = "-t test";
		String[] args = argstr.split(" ");
		CmdOptions.i().parse(args);

		assertTrue(CmdOptions.i().isSet("test"));
		assertEquals("test", CmdOptions.i().get("test")[0]);
	}

	@Test
	public void testMore() {
		CmdOptions.i().setSwitchCombination(true);
		CmdOptions.i().setShowOptions(false);
		String argstr = "-tf";
		String[] args = argstr.split(" ");
		CmdOptions.i().parse(args);

		assertTrue(CmdOptions.i().isSet("test"));
		assertTrue(CmdOptions.i().isSet("test2"));
	}

	@Test
	public void testMoreSwitches() {
		CmdOptions.i().setSwitchCombination(true);
		CmdOptions.i().setShowOptions(true);
		CmdOptions.i().setDontQuitOnError(true);
		String argstr = "-tsf";
		String[] args = argstr.split(" ");
		int e = CmdOptions.i().parse(args);

		assertEquals(1, e);
	}

	@Test
	public void testComplex() {
		CmdOptions.i().setSwitchCombination(true);
		CmdOptions.i().setShowOptions(true);
		String argstr = "-tf -c wth";
		String[] args = argstr.split(" ");
		CmdOptions.i().parse(args);

	}

	@After
	public void reset() {
		CmdOptions.i().resetValues();
	}
}
