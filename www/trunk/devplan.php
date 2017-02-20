<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Development Plan - FMSLogo</title>
		<meta name="description" content="Development Plan of FMSLogo, a  programming environment for Microsoft Windows">
		<?php include 'header.php' ?>
	</head>
	<body>
		<?php include 'menunav.php' ?>
		<div id="main">
			<article>
				<h1>Development Plan</h1>
				<p>
				There is a lot of work to do on FMSLogo.
				The code base lay in atrophy for five years before I picked it up.
				It will take a lot of work just to bring it up to date, even without making any major updates in functionality.
				Below is a rough outline of the development steps that I intend to take.
				Of course, I will always be looking to fix bugs and make small updates that enhance the usability along the way.
				Likewise, I'm willing to accept contributions from other developers that don't follow this development plan.
				</p>
				<ol>
					<li><b>Support Unicode</b><br>
					<p>
					FMSLogo is an ANSI program, which means it cannot easily support multiple languages.
					Furthermore, internally it has needed to reserve some characters for its own purpose, making it difficult to manipulate binary data.
					Once FMSLogo uses wxWidgets, it will be possible to port the internals to Unicode, which will make FMSLogo more compatible with modern operating systems and with non-English languages.
					</p>

					</li><li><b>Support 64-bit</b><br>
					<p>
					FMSLogo is a 32-bit program and making it run natively on modern hardware without an emulation layer is important for future-proofing it.
					</p>


					</li><li><b>Provide a Better Editor/Debugging Experience</b><br>
					<p>
					Once FMSLogo uses wxWidgets, there will be new UI controls available that will make it possible to have a modern editing/debugging experience, including breakpoints and more precise syntax error reporting.
					</p>

					</li><li><b>Port to GNU/Linux</b><br>
					<p>
					FMSLogo's heritage comes for MSWLogo, which is short for "Microsoft Windows Logo", so it naturally only runs on Windows and its API extensions are roughly 1:1 with Windows API.
					Porting FMSLogo to wxWidgets should make it easier to build a native version for GNU/Linux, with, perhaps, some reduced functionality.
					</p>


					</li><li><b>Add new API sets</b><br>
					<p>
					The overall set of things that FMSLogo has direct support for manpulating has been constant for 20 years.
					FMSLogo would benefit from new commands or language constructs that give access to regular expressions, text-to-speech, vector graphics, or animation.
					This is a long way off and I don't have anything specific in mind.
					</p>
				</li></ol>

				<p>
				One thing that won't change is FMSLogo's commitment to backward compatibility.
				It's important for teachers to be confident that they can download the latest FMSLogo and it will run code from their personal lesson plan that was written for MSWLogo.
				While certain compatibility breaks are unavoidable, I plan to avoid them when possible.
				</p>
			</article>
			<?php include 'aside.php' ?>
		</div>
		<?php include 'footer.php' ?>
	</body>
</html>
