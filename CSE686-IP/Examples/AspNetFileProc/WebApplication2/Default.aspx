<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication2._Default" ValidateRequest=false %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<!-- 
***************************************************************
* Default.aspx - Show file contents                           *
*                                                             *
* Jim Fawcett, CSE686 - Internet Programming, Summer 2009     *
***************************************************************
-->
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <style type="text/css">
      body { margin:4%; }
      #space1 { height:1em; }
      #space2 { height:1em; }
    </style>
</head>
<body>
    <h1>Show Files</h1>
    <form id="form1" runat="server">
    <div>    
    </div>
    <asp:TextBox ID="TextBox1" runat="server" Width="100%"></asp:TextBox>
    <div id="space1"></div>
    <asp:ListBox ID="ListBox1" runat="server" AutoPostBack="True" Height="150px" 
      Width="100%" onselectedindexchanged="ListBox1_SelectedIndexChanged"></asp:ListBox>
    <div id="space2"></div>
    <asp:TextBox ID="TextBox2" runat="server" Height="250px" Width="100%" 
      TextMode="MultiLine"></asp:TextBox>
    </form>
</body>
</html>
