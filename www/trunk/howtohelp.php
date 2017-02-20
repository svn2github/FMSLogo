<!DOCTYPE html>
<html lang="en">
	<head>
		<title>How to help - FMSLogo</title>
		<meta name="description" content="How you can help to improve FMSLogo, a  programming environment for Microsoft Windows">
		<?php include 'header.php' ?>
	</head>
	<body>
		<?php include 'menunav.php' ?>
		<div id="main">
			<article>
				<h1>How You Can Help</h1>

				<p>
				There are many ways to help improve FMSLogo and they don't all require hacking on C++ code.
				</p>

				<ul>
					<li>If you program in C++, then you can help by fixing bugs or implementing new features. 
					FMSLogo is built using completely free and zero-cost tools.
					There is a thumbnail sketch of how to setup a build environment at <a href="https://sourceforge.net/p/fmslogo/source/HEAD/tree/logo/trunk/HOWTO-BUILD.TXT">BUILD.TXT</a>.
					To my knowledge, I am the only one who has ever compiled FMSLogo, so don't expect this to be easy.
					Even if you are unable to build FMSLogo, if report where you get stuck in the FMSLogo ticketing system on SourceForge, you may help other developers.</li>

				  <li>The build system consists of hand-written Makefiles that have hard-coded paths that only work on my machine.
					If you know how to generalize the build to work like other GPL projects (with configure), that would be a great contribution.</li>

				  <li>I would like to bundle FMSLogo with lots of high-quality mini-applications written in FMSLogo that show off what it's capable of.
					I would like them to be written in a way that people can study, learn from, and improve them.
					Games are ideal, since my target will always be children and young adults.
					If you have a Logo program to donate, post a link in <a href="https://sourceforge.net/p/fmslogo/discussion/500407">the discussion forum</a>.
				  </li>

				  <li>Translate FMSLogo to a new language.
					  Each new translation of FMSLogo expands its potential audience.
					  Translators are expected to translate the text in the GUI and the names of each command.
					  Translating the manual is not necessary (but would be appreciated).
					  If you would like to translate FMSLogo to a new language, please post a comment to the <a href="https://sourceforge.net/p/fmslogo/discussion/500407">Public Forum</a> and I will send you further instructions.</li>

				  <li>I need real-world feedback on where FMSLogo should be improved. 
					  If you know where FMSLogo is lacking, please <a href="https://sourceforge.net/p/fmslogo/feature-requests/">post a feature request</a> or 
					  post a message in <a href="http://sourceforge.net/forum/forum.php?forum_id=500407">the discussion forum</a>.
					  Try to keep your suggestions based on practical experience (instead of abstract theories).
					  Also, please explain how your suggestion would improve FMSLogo as a learning tool for children.</li>

				  <li>File bugs. 
					  FMSLogo is full of them and they should all be tracked.
					  If you know of a bug, please file it in the <a href="https://sourceforge.net/p/fmslogo/bugs/">bug tracker</a>.
					  You must have a SourceForge account to create a bug ticket.</li>

				<li>If you're a GNU/Linux user, you can become a <a href="http://appdb.winehq.org/">WINE application maintainer</a> for FMSLogo.
					  I intend to port FMSLogo to GNU/Linux some day, but that could be years from now.
					  In the meantime, it'd be nice if it ran under WINE.
				</li>

				<li>
					Evangelize FMSLogo.
					Respond to questions posted on the Logo forum.
					If people get stuck or run into problems with FMSLogo, help them out.
					If you don't know how to help, try to connect them to someone who does.
				</li>

				<li>Whatever else you can think of!</li>
				</ul>
			</article>
			<?php include 'aside.php' ?>
		</div>
		<?php include 'footer.php' ?>
	</body>
</html>
