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

			conf.Options.Add(Options.XCode.Compiler.Exceptions.Enable);
		}

		[Configure(DevEnv.VisualStudio)]
		public void ConfigureVS(Configuration conf, Target target)
		{
			conf.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
			conf.Options.Add(Options.Vc.General.WarningLevel.Level4);
			conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
			conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4290"));

			conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
			conf.Defines.Add("_CRT_NONSTDC_NO_DEPRECATE");
		}

		[Configure(DevEnv.make)]
		public void ConfigureMake(Configuration conf, Target target)
		{
			conf.Options.Add(Options.Makefile.Compiler.Exceptions.Enable);
			conf.Options.Add(Options.Makefile.Compiler.Warnings.MoreWarnings);
			conf.Options.Add(Options.Makefile.Compiler.TreatWarningsAsErrors.Enable);

			conf.Options.Add(Options.Makefile.General.PlatformToolset.Clang);
			conf.Options.Add(Options.Makefile.Compiler.CppLanguageStandard.Cpp11);
			conf.AdditionalCompilerOptions.Add("-pthread");
			conf.AdditionalLinkerOptions.Add("-pthread");

			conf.Defines.Add("__STDC_LIB_EXT1__=1");
			/*conf.Defines.Add("strcpy_s=strcpy");
			conf.Defines.Add("sprintf_s=sprintf");
			conf.Defines.Add("vsnprintf_s=vsnprintf");
			conf.Defines.Add("_strcmp=_strcmp");*/
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