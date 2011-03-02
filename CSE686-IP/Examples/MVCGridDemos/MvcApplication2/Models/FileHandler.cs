///////////////////////////////////////////////////////////////
// FileHandler.cs - Model for handling files in About view   //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MvcApplication2.Models
{
  public class FileHandler
  {
    public string path { get; set; }
    public string[] files { get; set; }
    public bool GetFiles(string pattern)
    {
      try
      {
        int pos = path.LastIndexOf("Home");
        path = path.Substring(0, pos) + "Views\\Home";
        files = System.IO.Directory.GetFiles(path, pattern);
        return true;
      }
      catch { return false; }
    }
  }
}