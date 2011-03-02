///////////////////////////////////////////////////////////////
// CharacterModel.cs - Model of Charaters used in XmlModel   //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Web;
using System.IO;

namespace MvcApplication2.Models
{
  public class Character
  {
    public string Name { get; set; }
    public string Occupation { get; set; }
    public string Location { get; set; }
  }
  public class CharacterModel
  {
    public List<Character> Characters { get; set; }

    public CharacterModel()
    {
      Characters = new List<Character>();
    }
    public bool Fill(string path)
    {
      try
      {
        XDocument doc = XDocument.Load(path);
        var q = from chr in doc.Elements("characters").Elements("character") select chr;
        foreach(var elem in q)
        {
          Character c = new Character();
          c.Name = elem.Element("name").Value;
          c.Occupation = elem.Element("occupation").Value;
          c.Location = elem.Element("location").Value;
          Characters.Add(c);
        }
      }
      catch { return false; }
      return true;
    }
  }
}