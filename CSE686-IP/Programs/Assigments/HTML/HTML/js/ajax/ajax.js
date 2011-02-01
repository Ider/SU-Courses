
var xmlhttp;
function loadXMLDoc(url) {

    var txt, x, xx, i;
    if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp = new XMLHttpRequest();
    }
    else {// code for IE6, IE5
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    xmlhttp.onreadystatechange = presentXML;
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}


function presentXML() {
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        txt = "<table border='1'><tr><th>Title</th><th>Artist</th><th>COUNTRY</th></tr>";
        x = xmlhttp.responseXML.documentElement.getElementsByTagName("CD");
        for (i = 0; i < x.length; i++) {
            txt = txt + "<tr>";
            xx = x[i].getElementsByTagName("TITLE");
            {
                try {
                    txt = txt + "<td>" + xx[0].firstChild.nodeValue + "</td>";
                }
                catch (er) {
                    txt = txt + "<td> </td>";
                }
            }
            xx = x[i].getElementsByTagName("ARTIST");
            {
                try {
                    txt = txt + "<td>" + xx[0].firstChild.nodeValue + "</td>";
                }
                catch (er) {
                    txt = txt + "<td> </td>";
                }
            }
            xx = x[i].getElementsByTagName("COUNTRY");
            {
                try {
                    txt = txt + "<td>" + xx[0].firstChild.nodeValue + "</td>";
                }
                catch (er) {
                    txt = txt + "<td> </td>";
                }
            }
            txt = txt + "</tr>";
        }
        txt = txt + "</table>";
        document.getElementById('txtCDInfo').innerHTML = txt;
    }
}