<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Default.aspx.cs" Inherits="Wiki._Default" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <h2>
        Welcome to Wiki
    </h2>
    <div style="height: 400px; overflow-y:auto; word-wrap: break-word; word-break: normal;">
        <asp:Label ID="lblWiki" runat="server" Text="" Height="300px" Width="100%"></asp:Label>
        <asp:TextBox ID="txtWiki" runat="server" TextMode="MultiLine" Height="300px" Width="97%"></asp:TextBox>
    </div>
    <asp:Button ID="btnSumbit" runat="server" Text="Edit" OnClick="btnSumbit_Click" Width="120px" />
    &nbsp;
    <asp:Button ID="btnCancel" runat="server" Text="Cancel" Width="120px" OnClick="btnCancel_Click" />
</asp:Content>
