function onPageLoad(pageid) 
{
    setupLinks();

    // setup the navbar
    document.getElementById(pageid).className="currentpage";
}

function setupLinks() 
{
    
    for (var i = 0; i < document.links.length; i++) 
    {
        var link = document.links[i];

        link.className="blurred";
        link.setAttribute("onmouseover", "inFocus(this)");
        link.setAttribute("onmouseout",  "outFocus(this)");
    }
}

function inFocus(obj) 
{
    obj.className = 'infocus';
}
function outFocus(obj) 
{
    obj.className = 'blurred';
}

