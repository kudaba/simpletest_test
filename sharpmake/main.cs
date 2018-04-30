using Sharpmake;
using System;

namespace simpletest
{
	[Fragment, Flags]
	public enum Toolset
	{
		Gcc = 1,
		Clang = 2
	}

	public class CrossTarget : Target
	{
		public CrossTarget()
		{

		}
		public CrossTarget(Platform platform, DevEnv devEnv, Optimization optim, Toolset tools = Toolset.Gcc)
			: base(platform, devEnv, optim)
		{
			Toolset = tools;
		}

		public Toolset Toolset;
	}

	public static class Globals
	{
		public const string PathToRoot = @"\..";

		public const string PathToSrc = PathToRoot + @"\src";
		public const string PathToSimpleTest = PathToRoot + @"\simpletest";

		public const string PathToTmp = PathToRoot + @"\.temp";
		public const string PathToBuild = PathToTmp + @"\build";
		public const string PathToBin = PathToTmp + @"\bin";
		public const string PathToGen = PathToRoot + @"\projects";

		public static readonly CrossTarget[] DefaultTargets = new CrossTarget[]
		{
			new CrossTarget(Platform.win64,
				DevEnv.vs2015 | DevEnv.vs2017,
				Optimization.Debug | Optimization.Release),
			new CrossTarget(Platform.linux,
				DevEnv.make,
				Optimization.Debug | Optimization.Release,
				Toolset.Gcc | Toolset.Clang),
		};
	}

	[Generate]
	public class SimpleTestProject : Project
	{
		public SimpleTestProject() : base(typeof(CrossTarget))
		{
			AddTargets(Globals.DefaultTargets);
			SourceRootPath = "[project.SharpmakeCsPath]" + Globals.PathToSrc;
			AdditionalSourceRootPaths.Add("[project.SharpmakeCsPath]" + Globals.PathToSimpleTest);
		}

		[Configure]
		public void ConfigureAll(Configuration conf, CrossTarget target)
		{
			conf.ProjectPath = "[project.SharpmakeCsPath]" + Globals.PathToGen;
			conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.DevEnv]";

			conf.IncludePaths.Add("[project.SharpmakeCsPath]" + Globals.PathToSimpleTest);

			conf.IntermediatePath = "[project.SharpmakeCsPath]" + Globals.PathToBuild + @"\[target.Optimization]\[conf.ProjectFileName]";
			conf.TargetPath = "[project.SharpmakeCsPath]" + Globals.PathToBin;
			conf.TargetFileName = @"[conf.ProjectFileName]_[target.Optimization]";

			conf.Options.Add(Options.XCode.Compiler.Exceptions.Enable);
		}

		[Configure(DevEnv.VisualStudio)]
		public void ConfigureVS(Configuration conf, CrossTarget target)
		{
			conf.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
			conf.Options.Add(Options.Vc.General.WarningLevel.Level4);
			conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
			conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4290")); // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)

			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.Defines.Add("_CRT_NONSTDC_NO_DEPRECATE");
		}

		[Configure(DevEnv.make)]
		public void ConfigureMake(Configuration conf, CrossTarget target)
		{
			conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.Toolset]";

			conf.Options.Add(Options.Makefile.Compiler.Exceptions.Enable);
			conf.Options.Add(Options.Makefile.Compiler.Warnings.MoreWarnings);
			conf.Options.Add(Options.Makefile.Compiler.TreatWarningsAsErrors.Enable);

			if (target.Toolset == Toolset.Gcc)
				conf.Options.Add(Options.Makefile.General.PlatformToolset.Gcc);
			else
				conf.Options.Add(Options.Makefile.General.PlatformToolset.Clang);

			conf.Options.Add(Options.Makefile.Compiler.CppLanguageStandard.Cpp11);
			conf.AdditionalCompilerOptions.Add("-pthread");
			conf.AdditionalLinkerOptions.Add("-pthread");
		}
	}

	[Generate]
	public class SimpleTestSolution : Solution
	{
		public SimpleTestSolution() : base(typeof(CrossTarget))
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

		[Configure(DevEnv.make)]
		public void ConfigureMake(Configuration conf, CrossTarget target)
		{
			conf.SolutionFileName = "[solution.Name]_[target.Platform]_[target.Toolset]";
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