///////////////////////////////////////////////////////////////
// HomeController.cs - MVC Controller for SecondMVCDemo      //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Data.Linq;
using System.Web;
using System.Web.Mvc;

using MvcApplication2;
using System.Text.RegularExpressions;
using System.ComponentModel;

namespace MvcApplication2.Controllers
{
  [HandleError]
  public class HomeController : Controller
  {
    //---< action for Index view >-----------------------------

    public ViewResult Index()
    {
      ViewData["Message"] = "Grids Model-View-Controller Demo";
      return View();
    }
    //---< actions for Form view >-----------------------------

    [AcceptVerbs(HttpVerbs.Get)]
    public ViewResult Form()
    {
      ViewData["Message"] = "Form with model";
      return View();
    }

    [AcceptVerbs(HttpVerbs.Post)]
    public ViewResult Form(MvcApplication2.Models.FormModel model)
    {
      // Note: 
      // MVC Framework instantiates an instance of FormModel, 
      // a class we defined in Models folder, and passes the
      // instance to this method when reponding to Home/Form.
      // You can use any class defined in the Models folder
      // as an argument to a Controller method

      // ViewData is a dictionary available to both Controller
      // methods and to inline code in a view.

      ViewData["Message"] = "Form with model Postback";

      // form validation

      if (string.IsNullOrEmpty(model.Name))
        ViewData["NameError"] = true;
      else
        ViewData["NameError"] = false;

      if (string.IsNullOrEmpty(model.Phone))
        ViewData["PhoneError"] = true;
      else
        ViewData["PhoneError"] = false;

      if (string.IsNullOrEmpty(model.Email))
      {
        ViewData["EmailError"] = true;
      }
      else if (!Regex.IsMatch(model.Email, ".+\\@.+\\..+"))
        ViewData["EmailError"] = true;
      else
        ViewData["EmailError"] = false;

      // bind to the model FormModel (see call argument)
      
      return View(model);
    }
    //---< action for grid view >------------------------------

    [AcceptVerbs(HttpVerbs.Get)]
    public ActionResult Grid(Models.GridModel model)
    {
      // Grid uses a collection of characters, but
      // View binding only works for simpler models, so we will 
      // save our model, read from an XML file here, into the 
      // Session dictionary for later use.  Remember that
      // The controllers are recreated with every request and
      // so can't be used to save state, except for statics.

      string file = Server.MapPath("..\\App_Data\\XmlModelData.xml");
      Session["file"] = file;
      model.Fill(file);  // look at the GridModel in the models folder
      Session["GridModel"] = model;
      ViewData["Message"] = "Grid from XML Character Model";

      // Most of the Grid controller functions redirect to Show
      
      return RedirectToAction("Show");
    }
    //----< show populated grid >------------------------------

    public ActionResult Show(Models.GridModel model)
    {
      model = (Models.GridModel)Session["GridModel"];
      return View(model);
    }
    //----< prepare edit >-------------------------------------

    public ActionResult Edit(string id)
    {
      // An Html.ActionLink invokes this method and passes its id attribute.
      // Note that ActionLinks do an Http Get, not a Post, so no model
      // data is sent - we need to get it out of the Session.

      Models.GridModel model = (Models.GridModel)Session["GridModel"];
      int selected = Int32.Parse(id);
      for (int i = 0; i < model.Characters.Count; ++i)
      {
        if (i != selected)
          model.Characters[i].Checked = false;
        else
          model.Characters[i].Checked = true;
      }
      return View(model);
    }
    //----< insert new record >--------------------------------

    public ActionResult Insert(Models.GridCharacter cmodel)
    {
      // We got here from a submit button on the Insert form, one of two
      // in the Show.aspx view.  Therefore, model data was sent to us
      // via the cmodel parameter.

      Models.GridModel model = Session["GridModel"] as Models.GridModel;
      model.Characters.Add(cmodel);
      string file = Session["file"] as string;
      model.Save(model, file);
      return RedirectToAction("Show");
    }
    //----< delete record >------------------------------------

    public ActionResult Delete(string id)
    {
      // We got here from an ActionLink, so no data is posted,
      // but we do get the link's id.

      int selected = Int32.Parse(id);
      Models.GridModel model = Session["GridModel"] as Models.GridModel;
      model.Characters.RemoveAt(selected);
      string file = Session["file"] as string;
      model.Save(model, file);
      return RedirectToAction("Show");
    }
    //----< save results of edit >-----------------------------

    public ActionResult Save(Models.GridCharacter cmodel)
    {
      // We get here when a "Save" submit button is clicked, so we
      // get model data sent up via the cmodel parameter.

      int selected = (int)Session["Selected"];
      Models.GridModel model = Session["GridModel"] as Models.GridModel;
      model.Characters[selected].Name = cmodel.Name;
      model.Characters[selected].Occupation = cmodel.Occupation;
      model.Characters[selected].Location = cmodel.Location;
      model.Characters[selected].Checked = false;
      string file = Session["file"] as string;
      model.Save(model, file);
      return RedirectToAction("Show");
    }
    //---< action for grid view >------------------------------

    [AcceptVerbs(HttpVerbs.Post)]
    public ActionResult Grid(Models.GridModel _model, int? i)
    {
      // Should never get here as there no longer is a submit button
      // on the Show.aspx view.

      ViewData["Message"] = "Grid from Postback XML Character Model";
      return RedirectToAction("Show");
    }
    //---< action for SqlModel view >--------------------------
    //
    // http://msdn.microsoft.com/en-us/library/bb425822.aspx
    // http://www.asp.net/mvc/tutorials/creating-model-classes-with-linq-to-sql-cs
    //
    public ViewResult SqlModel(Models.CharacterDataDataContext cdc)
    {
      ViewData["Message"] = "Sql Character Model";
      return View(cdc);
    }
    //---< action for XmlModel view >-----------------------------

    public ViewResult XmlModel(MvcApplication2.Models.CharacterModel model)
    {
      string file = Server.MapPath("..\\App_Data\\XmlModelData.xml");
      model.Fill(file);
      ViewData["Message"] = "XML Character Model";
      return View(model);
    }
    //---< action for About view >-----------------------------

    public ViewResult About(Models.FileHandler fh)
    {
      string path = Server.MapPath(".");
      fh.path = path;
      fh.GetFiles("*.*");
      return View(fh);
    }
  }
}
