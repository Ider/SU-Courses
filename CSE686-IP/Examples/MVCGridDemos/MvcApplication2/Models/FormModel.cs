///////////////////////////////////////////////////////////////
// FormModel.cs - Model of input used in FormModel           //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MvcApplication2.Models
{
  public class FormModel
  {
    public string Name { get; set; }
    public string Email { get; set; }
    public string Phone { get; set; }
  }
}