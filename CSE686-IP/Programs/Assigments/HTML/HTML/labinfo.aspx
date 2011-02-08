<%@ Page Title="Lab Assiment Information" Language="C#" MasterPageFile="~/master.Master"
    AutoEventWireup="true" CodeBehind="labinfo.aspx.cs" Inherits="HTML.labinfo" %>

<%@ MasterType VirtualPath="master.master" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <script src="js/ajax/load_lab.js" type="text/javascript"></script>
    <style type="text/css">
        .map
        {
            border: 1px solid #a62315;
            vertical-align: top;
            white-space: nowrap;
        }
        .map thead
        {
            color: #fff;
            background-image: -moz-linear-gradient(0% 22px 90deg, #a62315, #f47321);
            background-image: -webkit-gradient(linear, 0% 0%, 0% 70%, from(#f47321), to(#a62315));
            background-color: #f47321;
            font-weight: bold;
        }
        .map tbody td
        {
            vertical-align: top;
            width: 33.3%;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="caption">
        <asp:Label ID="lblCaption" runat="server" Text="Lab Assignment Information"></asp:Label>
    </div>
    <div id="lab">
    </div>
    <script type="text/javascript">
        loadXMLLab("lab", "map");
    </script>
</asp:Content>
