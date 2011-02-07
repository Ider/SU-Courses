<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="test.aspx.cs" Inherits="HTML.test" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Test Page</title>
    <link href="styles/tableformat.css" rel="stylesheet" type="text/css" />
    <link href="styles/icon.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        .map td.fileName
        {
            width: 70%;
        }
        .map td.fileType
        {
            width: 10%;
        }
        .map td.lastModified
        {
            width: 20%;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div class="caption">
        <asp:Label ID="lblCurPath" runat="server" Text="[Current Path]"></asp:Label>
    </div>
    <div style="border: 1px solid #a62315; min-width: 600px; width: 100%;">
        <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map"
            style="border: 0px solid #fff;">
            <thead>
                <tr>
                    <td class="fileName">
                        Name
                    </td>
                    <td class="fileType">
                        Type
                    </td>
                    <td class="lastModified">
                        Last Modified
                    </td>
                </tr>
            </thead>
        </table>
        <div style="width: 100%; overflow-y: scroll; height: 200px;">
            <asp:Literal ID="litList" runat="server"></asp:Literal></div>
    </div>
    <asp:Button ID="btnSumbit" runat="server" Text="[Submit]" />
    </form>
</body>
</html>
