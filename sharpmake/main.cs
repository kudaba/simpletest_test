using Sharpmake;

namespace simpletest
{
	public static class Globals
	{
		public const string PathToRoot = @"\..";

		public const string PathToSrc = PathToRoot + @"\src";
		public const string PathToSimpleTest = PathToRoot + @"\simpletest";

		public const string PathToTmp = PathToRoot + @"\.temp";
		public const string PathToBuild = PathToTmp + @"\build";
		public const string PathToBin = PathToTmp + @"\bin";
		public const string PathToGen = PathToRoot + @"\projects";

		public static readonly ITarget[] DefaultTargets = new ITarget[]
		{
			new Target(Platform.win64,
				DevEnv.vs2015 | DevEnv.vs2017 | DevEnv.make,
				Optimization.Debug | Optimization.Release)
		};
	}

	[Generate]
	public class SimpleTestProject : Project
	{
		public SimpleTestProject()
		{
			AddTargets(Globals.DefaultTargets);
			SourceRootPath = "[project.SharpmakeCsPath]" + Globals.PathToSrc;
			AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]" + Globals.PathToSimpleTest);
		}

		[Configure]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.ProjectPath = "[project.SharpmakeCsPath]" + Globals.PathToGen;
			conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.DevEnv]";

			conf.IncludePaths.Add("[project.SharpmakeCsPath]" + Globals.PathToSimpleTest);

			conf.IntermediatePath = "[project.SharpmakeCsPath]" + Globals.PathToBuild + @"\[conf.ProjectFileName]";
			conf.TargetPath = "[project.SharpmakeCsPath]" + Globals.PathToBin;
			conf.TargetFileName = @"[conf.ProjectFileName]";

		}
	}

	[Generate]
	public class SimpleTestSolution : Solution
	{
		public SimpleTestSolution()
		{
			AddTargets(Globals.DefaultTargets);
		}

		[Configure]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.SolutionPath = "[solution.SharpmakeCsPath]" + Globals.PathToGen;
			conf.SolutionFileName = "[solution.Name]_[target.Platform]_[target.DevEnv]";

			conf.AddProject<SimpleTestProject>(target);
		}
	}
	public static class Main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments args)
		{
			KitsRootPaths.SetKitsRoot10ToHighestInstalledVersion();
			args.Generate<SimpleTestSolution>();
		}
	}
}