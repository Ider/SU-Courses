///////////////////////////////////////////////////////////////
// GridModel.cs - Character Model persisted to XML file      //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Spring 2011   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;

namespace MvcApplication2.Models
{
  public class GridCharacter
  {
    public string Name { get; set; }
    public string Occupation { get; set; }
    public string Location { get; set; }
    public bool Checked { get; set; }
  }
  public class GridModel
  {
    public List<GridCharacter> Characters { get; set; }
    public string Radio { get; set; }

    public GridModel()
    {
      Characters = new List<GridCharacter>();
      Radio = "";
    }
    public bool Fill(string path)
    {
      try
      {
        XDocument doc = XDocument.Load(path);
        var q = from chr in doc.Elements("characters").Elements("character") select chr;
        foreach(var elem in q)
        {
          GridCharacter c = new GridCharacter();
          c.Name = elem.Element("name").Value;
          c.Occupation = elem.Element("occupation").Value;
          c.Location = elem.Element("location").Value;
          c.Checked = false;
          Characters.Add(c);
        }
      }
      catch { return false; }
      return true;
    }
    public bool Save(Models.GridModel model, string path)
    {
      try
      {
        XDocument doc = new XDocument();
        XElement elm = new XElement("characters");
        foreach (GridCharacter c in model.Characters)
        {
          XElement character = new XElement("character");
          XElement name = new XElement("name");
          name.Value = c.Name;
          XElement occupation = new XElement("occupation");
          occupation.Value = c.Occupation;
          XElement location = new XElement("location");
          location.Value = c.Location;
          character.Add(name);
          character.Add(occupation);
          character.Add(location);
          elm.Add(character);
        }
        doc.Add(elm);
        doc.Save(path);
      }
      catch { return false; }
      return true;
    }
  }
}