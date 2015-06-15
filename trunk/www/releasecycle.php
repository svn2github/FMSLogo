<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Release Cycle - FMSLogo</title>
		<meta name="description" content="Release Cycle of FMSLogo, a  programming environment for Microsoft Windows">
		<?php include 'header.php' ?>
	</head>
	<body>
		<?php include 'menunav.php' ?>
		<div id="main">
			<article>
				<h1>Release Cycle</h1>
				<p>
					The most fundamental aspect to understanding the release cycle is  understanding how FMSLogo version numbers work.
					FMSLogo uses three numbers for its version number, separated by dots, as in:
				</p>
				<p style="margin-left:20px">FMSLogo <i>major</i>.<i>minor</i>.<i>bugfix</i></p>
				<p>
					For example, FMSLogo 6.10.1 has a major version of 6, a minor version of 10, and a bugfix version of 1.
					In addition, there are "developer snapshots" versions that are not publicly released.
					Developer snapshots may be completely untested.
					Developer snapshots are distinguished from "official" revisions by appending a "+" character to the most recent revision.
				</p>
				<p>
					A change to the <b>bugfix</b> version is required by any of the following:
				</p>
				<ul>
					 <li>Fixes for significant regressions introduced in the latest minor or bugfix revision</li>
					 <li>Minor improvements to the manual</li>
					 <li>Performance improvements</li>
				</ul>
				<p>
					A change to the <b>major</b> version is required by any of the following:
				</p>
				<ul>
					<li>A significant change to the look and feel of the user interface</li>
					<li>A significant change usage paradigm of the user interface</li>
					<li>Incompatibilities in Logo programs that require significant rework to get the program to run properly again</li>
				</ul>
				<p>
					Before I release any new version of FMSLogo, I run it through a regression test suite, on both Windows XP and Windows 95.
					This includes automated tests, manual tests, and testing that the "extras" still work correctly.
				</p>
				<p>
					I release a new minor version of FMSLogo about every three months, somewhere near the middle of the month.
					I release a new bugfix version only when necessary.
					Due to the amount of time required to test each version of FMSLogo, I only release a bugfix version to address problems that can't wait until the next minor revision.
					In other words, if I release a bugfix version, it's because I did something very bad in the previous release.
				</p>
			</article>
			<?php include 'aside.php' ?>
		</div>
		<footer>
			<a href="http://sourceforge.net/projects/fmslogo"><img id="sourceforge" src="media/sflogo.png" width="120" height="30" alt="Get FMSLogo at SourceForge.net. Fast, secure and Free Open Source software downloads"></a>
		</footer>
	</body>
</html>