<%@ Page Title="File View" Language="C#" MasterPageFile="~/master.Master" AutoEventWireup="true"
    CodeBehind="fileview.aspx.cs" Inherits="HTML.fileview" %>

<%@ MasterType VirtualPath="master.master" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
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
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
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
            <asp:Literal ID="litList" runat="server"></asp:Literal>
        </div>
    </div>
    <div class="caption">
        <asp:Label ID="Label1" runat="server" Text="C# Files"></asp:Label>
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
            <asp:Literal ID="litCsharp" runat="server"></asp:Literal>
        </div>
    </div>
    <div class="caption">
        <asp:Label ID="Label2" runat="server" Text="ASPX Files"></asp:Label>
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
            <asp:Literal ID="litASPX" runat="server"></asp:Literal>
        </div>
    </div>
    <div class="caption">
        <asp:Label ID="lblContent" runat="server" Text="Please select a file..."></asp:Label>
        &nbsp;</div>
    <div id="divContent" style="border: 1px solid #a62315; min-width: 600px; width: 100%;
        height: 400px; overflow: auto;">
        <asp:Literal ID="litContent" runat="server">        </asp:Literal>
    </div>
    <div id="divHidden" style="display: none;">
        <asp:Button ID="btnSubmit" runat="server" Text="[Submit]" OnClick="btnSubmit_Click" />
        <asp:HiddenField ID="hfFileName" runat="server" />
        <asp:HiddenField ID="hfIsFolder" runat="server" />
    </div>
    <script type="text/javascript">

        function submitClick(filename, isFile) {
            var name = document.getElementById("<%=hfFileName.ClientID %>");
            var flag = document.getElementById("<%=hfIsFolder.ClientID %>");
            name.value = filename;
            flag.value = isFile;
            var btn = document.getElementById("<%=btnSubmit.ClientID %>");
            if (btn)
                btn.click();
            else {
                alert("Sorry, unable to submit your request!");
            }
        }

    </script>
</asp:Content>
