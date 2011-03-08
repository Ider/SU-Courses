<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<System.DateTime?>" %>
<link href="../../../Content/jquery.ui.datepicker.css" rel="stylesheet" type="text/css" />
<script src="../../../Scripts/jquery.ui.datepicker.js" type="text/javascript"></script>
<script src="../../../Scripts/jquery.ui.widget.js" type="text/javascript"></script>
<script src="../../../Scripts/jquery.ui.core.js" type="text/javascript"></script>
<script type="text/javascript">

    $(function () {

        $(".datePicker").datepicker({ showOn: 'both', changeMonth: true,
            changeYear: true
        });

    });

</script>
<%=Html.TextBox("", (Model.HasValue ? Model.Value.ToString("MM/dd/yyyy HH:mm:ss") : string.Empty), new { @class = "datePicker" })%>
