var xmlhttp;
var container;
var cssclass;
var imgsrc;
function loadXMLLab(div, style, imgandsrc) {

    container = div;
    cssclass = style ? style : "";
    imgsrc = imgandsrc ? imgandsrc : "";
    if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp = new XMLHttpRequest();
    }
    else {// code for IE6, IE5
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    xmlhttp.onreadystatechange = presentLab;
    xmlhttp.open("GET", "lab.xml", true);
    xmlhttp.send();
}

function presentLab() {
    var txt, x, xx, i;
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        txt = "<table width=\"100%\" border=\"0\" align=\"left\" cellpadding=\"5\" "
    + "cellspacing=\"0\" class=\"" + cssclass + "\">";

        txt = txt + "<thead> <tr><td>Requirements</td><td> Pages</td><td>Scores</td></tr></thead>"
        txt = txt + "<tbody><tr>";

        txt = txt + "<td>" + getRequirmentList() + "</td>"
        txt = txt + "<td>" + getPageList() + "</td>"
        txt = txt + "<td>" + getScoreList() + "</td>"

        txt = txt + "</tr></table>";
        document.getElementById(container).innerHTML = txt;
        if (imgsrc) {
            try {
                var str = imgsrc.split(",");
                var img = document.getElementById(str[0]);

                img.src = str[1];
            }
            catch (er) {
            }
        }
    }
}


function getRequirmentList() {
    var list, i;
    var text, url, link;
    var x = xmlhttp.responseXML.documentElement.getElementsByTagName("requirement");
    link = "http:\/\/www.ecs.syr.edu/faculty/fawcett/handouts/CSE686/assignments/";
    list = "<ul>";

    for (i = 0; i < x.length; i++) {

        try {
            url = x[i].getElementsByTagName("url")[0].firstChild.nodeValue;
            text = x[i].getElementsByTagName("text")[0].firstChild.nodeValue;
        }
        catch (er) {
            url = "#";
            text = "";
        }

        list = list + "<li><a href='" + link + url + "'>" + text + "</a></li>"
    }
    list = list + "</ul>"

    return list;
}

function getPageList() {

    var list, i;
    var text, url;
    var x = xmlhttp.responseXML.documentElement.getElementsByTagName("page");
    list = "<ul style='list-style-type: decimal;'>";

    for (i = 0; i < x.length; i++) {

        try {
            url = x[i].getElementsByTagName("url")[0].firstChild.nodeValue;
            text = x[i].getElementsByTagName("text")[0].firstChild.nodeValue;

            list = list + "<li><a href='" + url + "'>" + text + "</a></li>"
        }
        catch (er) {
            url = "#";
            text = "<span style='color:gray'>Under Construction...</span>";

            list = list + "<li>" + text + "</li>";
        }
    }
    list = list + "</ul>"
    return list;
}

function getScoreList() {

    var list, i;
    var text;
    var x = xmlhttp.responseXML.documentElement.getElementsByTagName("score");
    list = "<ul>";

    for (i = 0; i < x.length; i++) {

        try {
            text = x[i].firstChild.nodeValue;
        }
        catch (er) {
            text = "<span style='color:gray'>Ungraged</span>";
        }

        list = list + "<li>" + text + "</a></li>"
    }
    list = list + "</ul>"

    return list;
}
