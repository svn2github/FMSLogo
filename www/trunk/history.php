<!DOCTYPE html>
<html lang="en">
	<head>
		<title>History - FMSLogo</title>
		<meta name="description" content="History of Logo, a programming environment for Microsoft Windows">
		<?php include 'header.php' ?>
	</head>
	<body>
		<?php include 'menunav.php' ?>
		<div id="main">
			<article>
				<h1>A Brief History Of FMSLogo</h1>
				<p>
				Seymour Papert (and others) designed the Logo language to be powerful enough for computer research, but simple enough so that it could be enjoyed by children.
				Papert used Logo to conduct Artificial Intelligence and Robotics research at the Massachusetts Institute of Technology.
				One of the robots that Logo controlled had a dome-shaped protective casing over its electronics that made it resemble a turtle.
				As personal computers became more affordable, the physical turtle was replaced by a virtual turtle on a computer screen.
				The virtual turtle was given a pen to help it fit into the familiar world of childhood learning.
				Drawing is already a natural part of childhood, but drawing with Logo is different than drawing with crayons.
				To draw with Logo, you must learn to think about drawing, enough so that you can teach a complete idiot (the turtle) how to draw.
				</p>

				<p>
				Throughout the 1980s, as computers became more affordable, Logo was integrated into the curiculum of many schools.
				This led to a proliferation of different Logo software packages, each sharing the core spirit of Logo, but designed for specific computers.
				</p>

				<p>
				In the early 1990s Brian Harvey, a lecturer at UC Berkley, wanted to write a computer science textbook for non-professional programmers.
				He selected Logo as the language for his textbook.
				At this time, there were many Logo enviornments, each with their own incompatibilies, some of which were no longer available for purchase.
				To overcome the incompatibilies between different versions of Logo, Brian created a new version of Logo and ported it to every popular computer of the time.
				He named it UCBLogo and based his textbook on it.
				UCBLogo was written 1993 and given away free-of-charge.
				</p>

				<p>
				Shortly thereafter, a like-minded Englishman named George Mills was inspiried by UCBLogo.
				He ported UCBLogo to a C++ toolkit from Borland that ran on Microsoft Windows, thereby creating MSWLogo (short for "Microsoft Windows Logo").
				MSWLogo retained the UCBLogo base, but added new commands that took advantage of features unique to Microsoft Windows.
				This became the standard Logo for Windows.
				</p>

				<p>
				To understand what an accomplishment UCBLogo and MSWLogo were, it's worth considering what the world of personal computing was like in 1993.
				If home users had any Internet connection at all, it was dialup at 14.4 Kbps and they were charged by the minute.
				HTTP was not yet a standard.
				The fastest Intel CPU was the Pentium running at 66 Mhz.
				Manufacturers added a "turbo mode" button that would slow down the Penitum so that software written for older CPUs would function properly.
				Windows 95 had not yet been released and the personal computer market was dominated by IBM clones that ran DOS or Windows 3.1.
				In the operating systems of the time, all memory was shared by all programs and a bug in one could crash your entire computer.
				Most video cards only supported a limited number of colors: some couldn't even show 256 colors.
				Programmers were accustomed to writing software for a specific computers and throwing it away when the computer became obsolete.
				</p>

				<p>
				In 2004, I was looking to start a computer workshop with Jim Foster at the Boys and Girls Club in Bellevue, Washington.
				I picked Logo, which led to MSWLogo, since all of the machines in their computer lab ran Windows 98.
				I made a few small enhancements to MSWLogo to improve the workflow in my workshop and sent them to George Mills for integration into the next version of MSWLogo.
				By that time, George no longer had time to work on MSWLogo, so I created my own version.
				Soon afterward, I got a job at Microsoft and I asked the legal department if it was okay to continue working on MSWLogo.
				They said there was no conflict of interest, but I couldn't call it "Microsoft Windows Logo", as that made it sound like it was created by Microsoft, which was trademark infrigement.
				As I looked for a new name, George, whose loved ones had recently contracted Multiple Sclerosis, said that he wanted "MS" to be in the name.
				So began the "FMS" prefix, which stands for "Fight Multiple Scleroris".
				</p>

			</article>
			<?php include 'aside.php' ?>
		</div>
		<?php include 'footer.php' ?>
	</body>
</html>
