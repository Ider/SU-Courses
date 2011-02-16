<%@ Page Title="" Language="C#" MasterPageFile="~/master.Master" AutoEventWireup="true" CodeBehind="description.aspx.cs" Inherits="HTML.final_project.description" %>
<%@ Register src="fpnavigator.ascx" tagname="fpnavigator" tagprefix="uc1" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style type="text/css">

 p.MsoNormal
	{margin-bottom:.0001pt;
	font-size:12.0pt;
	font-family:"Courier New";
	        margin-left: 0in;
            margin-right: 0in;
            margin-top: 0in;
        }
p.MsoFootnoteText
	{margin-bottom:.0001pt;
	font-size:10.0pt;
	font-family:"Courier New";
	        margin-left: 0in;
            margin-right: 0in;
            margin-top: 0in;
        }
        .style1
        {
            vertical-align: super;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
<uc1:fpnavigator ID="fpnavigator1" runat="server" />
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <!--[if supportFields]><b style="mso-bidi-font-weight:normal">
        <i style="mso-bidi-font-style:normal">
        <span style="font-size:14.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        PRIVATE </span></i></b><![endif]--><!--[if supportFields]><![endif]-->
        <b style="mso-bidi-font-weight:normal"><i style="mso-bidi-font-style:normal">
        <span style="font-size:14.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Final Project #1– Software Development Project Center</span></i><span 
            style="font-size:14.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <span style="mso-spacerun:yes">&nbsp;&nbsp;&nbsp;</span><o:p></o:p></span></b></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        due Last day of Class<o:p></o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <b style="mso-bidi-font-weight:normal">
        <span style="font-size:11.5pt;mso-bidi-font-size:
10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></b></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <b style="mso-bidi-font-weight:normal"><u>
        <span style="mso-bidi-font-size:12.0pt;
font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">Purpose:</span></u></b><b style="mso-bidi-font-weight:
normal"><span 
            style="mso-bidi-font-size:12.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;"><o:p></o:p></span></b></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        You are a software developer and have been asked to develop a website and 
        associated web service to support development activities for projects in your 
        company.<span style="mso-spacerun:yes">&nbsp; </span>The site is required to 
        support recording and management of software requirements, work package 
        descriptions, bug reports, and status reports.<span style="mso-spacerun:yes">&nbsp;
        </span>The site will also provide a Wiki, used for communication between teams 
        and also between developers and management.<span style="mso-spacerun:yes">&nbsp;
        </span>You are also asked to provide a WCF-based service that supports client 
        side application access to the data stored on this site, and two client 
        applications that can create, modify, and delete bug reports and status reports.
        <o:p>
        </o:p>
        </span>
    </p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <b style="mso-bidi-font-weight:normal"><u>
        <span style="mso-bidi-font-size:12.0pt;
font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">Requirements:<o:p></o:p></span></u></b></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        The requirements for this project are to provide:<span style="mso-tab-count:1">&nbsp;&nbsp;&nbsp;&nbsp;
        </span>
        <o:p>
        </o:p>
        </span>
    </p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">1.
<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        A website that supports creating, modifying, and deleting software requirements, 
        work package descriptions, bug reports, and status reports.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">a.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Software requirements are stored in an SQL Server database, have an immutable 
        number, title, date, and text statement.<span style="mso-spacerun:yes">&nbsp;
        </span>Any requirement may also have an associated issues text statement<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">b.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        All bug reports are stored in (the same) XML file, have an immutable number, 
        title, date, issue text, and resolution text, which initially is blank.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">c.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Status reports are stored in the SQL Server database, have an immutable number, 
        title, date, work package reference, and status text.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">d.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        All text fields in requirements, work packages, bug reports, and status reports 
        must support text of an open-ended size and views of that text should present 
        the equivalent of several paragraphs to the user for both viewing and for 
        modification.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">2.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        A WCF-based web service that provides create, review, update, and delete (CRUD) 
        access for the bug and status reports.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">3.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Two WPF client applications that use this service to support CRUD operations.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">4.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        A separate website that supports a Wiki intended to provide communication across 
        a development project and also inter-team communication.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">a.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Please provide a project wide section to which everyone has read access but only 
        the project manager and team leaders have write access.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">b.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Provide the ability for each team to create a section in the Wiki for the team.<span 
            style="mso-spacerun:yes">&nbsp; </span>All project members have read access, 
        but only project members, including the team lead, have write access.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">5.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        You are required to implement one of these sites in Asp.Net and the other in 
        Asp.Net MVC.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">6.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Login access that forces a link to any page to verify that you are a valid user, 
        by checking the current session to see if you are currently logged in, otherwise 
        redirecting you to a login page.<span style="mso-spacerun:yes">&nbsp; </span>You 
        may<span style="mso-spacerun:yes">&nbsp; </span>use the Asp.Net provided login 
        code, Asp.Net MVC login code, or develop a user control for this that you will 
        make part of every page.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.25in;text-align:justify;text-indent:
-.25in;mso-list:l0 level1 lfo1;mso-hyphenate:none;tab-stops:list .25in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">7.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Your site <b style="mso-bidi-font-weight:normal">shall</b> use:<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">a.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Both SQL server database(s) and XML file(s), of your design, to store state of 
        the site, as described above.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">b.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Use LINQ to access state data.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">c.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Either Silverlight or HTML5 for some parts of your site.<o:p></o:p></span></p>
    <p class="MsoNormal" style="margin-left:.6in;text-align:justify;text-indent:-.25in;
mso-list:l0 level2 lfo1;mso-hyphenate:none;tab-stops:list .6in">
        <![if !supportLists]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;
mso-fareast-font-family:Tahoma"><span style="mso-list:Ignore">d.<span 
            style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
        </span></span></span><![endif]>
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Pages using each of the models: HTML with Javascript and CSS, Asp.Net, and 
        Asp.Net MVC.<span style="mso-spacerun:yes">&nbsp; </span>Note that you may use 
        more than one project for your site.<o:p></o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        You are expressly requested to refrain from using site editors like Dreamweaver, 
        FrontPage, or other Web designers.<span style="mso-spacerun:yes">&nbsp; </span>
        You may use any of the facilities of Visual Studio 2010 or any other text editor 
        of your choosing.<o:p></o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        For the final demo, you will be asked to host your site in IIS on your own 
        machine and do all navigation via links provided on the pages of your site<a 
            href="#_ftn1" name="_ftnref1" style="mso-footnote-id:ftn1" title=""><span 
            class="style1"><span style="mso-special-character:footnote"><![if !supportFootnotes]><span style="font-size:9.0pt;mso-bidi-font-size:
10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;mso-fareast-font-family:&quot;Times New Roman&quot;;
mso-ansi-language:EN-US;mso-fareast-language:EN-US;mso-bidi-language:AR-SA">[1]</span><![endif]></span></span></a>.<o:p></o:p></span></p>
    <p class="MsoNormal" 
        style="text-align:justify;mso-hyphenate:none;tab-stops:-.5in">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <p class="MsoNormal" style="text-align:justify;mso-hyphenate:none">
        <b style="mso-bidi-font-weight:normal"><u>
        <span style="font-size:11.0pt;
mso-bidi-font-size:12.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">Please 
        Note:<o:p></o:p></span></u></b></p>
    <p class="MsoNormal" 
        style="text-align:justify;mso-hyphenate:none;tab-stops:-.5in">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        Part of your grade is based on designing a pleasing website to meet these 
        requirements.<span style="mso-spacerun:yes">&nbsp; </span>I will not specify the 
        details of that design.<span style="mso-spacerun:yes">&nbsp; </span><b><i>You</i></b> 
        must decide the visual aspects and details for each page.<o:p></o:p></span></p>
    <p class="MsoNormal" 
        style="text-align:justify;mso-hyphenate:none;tab-stops:-.5in">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <p class="MsoNormal" 
        style="text-align:justify;mso-hyphenate:none;tab-stops:-.5in">
        <span style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
        <o:p>
        &nbsp;</o:p></span></p>
    <div style="mso-element:footnote-list">
        <![if !supportFootnotes]>
        <br clear="all" />
        <hr align="left" size="1" width="33%" />
        <![endif]>
        <div id="ftn1" style="mso-element:footnote">
            <p class="MsoFootnoteText">
                <a href="#_ftnref1" name="_ftn1" style="mso-footnote-id:ftn1" title="">
                <span class="style1">
                <span style="font-size:
9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;">
                <span style="mso-special-character:footnote"><![if !supportFootnotes]>
                <span style="font-size:9.0pt;mso-bidi-font-size:
10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;;mso-fareast-font-family:&quot;Times New Roman&quot;;
mso-ansi-language:EN-US;mso-fareast-language:EN-US;mso-bidi-language:AR-SA">[1]</span><![endif]></span></span></span></a><span 
                    style="font-size:9.0pt;mso-bidi-font-size:10.0pt;font-family:&quot;Tahoma&quot;,&quot;sans-serif&quot;"> 
                That means you’re not supposed to navigate through a directory structure to find 
                a page.<o:p></o:p></span></p>
        </div>
    </div>
</asp:Content>
