<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0, user-scalable=no">
<meta name="keywords" content="FMSLogo, Logo, MSWLogo, Programming">
<meta name="robots" content="index, follow">
<meta name="author" content="David Costanzo">
<link rel="stylesheet" href="media/style.css" type="text/css">
<link rel="shortcut icon" href="media/favicon.ico" type="image/x-icon">
<link rel="icon" href="media/favicon.ico" type="image/x-icon">
<script src="javascript/jquery-1.10.2.min.js"></script>
<!--[if lt IE 9]>
<script src="javascript/html5.js"></script>
<![endif]-->
<script type="text/javascript">
		$(document).ready(function() {
			$('.menubutton').click(function() {
				$('nav').slideToggle('slow');
			});
		});
</script>
<script>
	$(function(){
		// Get everything after the initial '/'
		var page = window.location.pathname.substr(1);
		if (page === '' || page === 'index') {
			// The 'index" link goes to the site root.
			page = '/';
		}

		// Make the navlink that cooresponds to the page look active.
		$('a[href*="'+page+'"]').addClass('active');
	});
</script>
