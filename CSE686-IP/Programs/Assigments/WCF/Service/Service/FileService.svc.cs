using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Web;
using System.IO;

namespace Service
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "FileService" in code, svc and config file together.
    public class FileService : IFileService
    {
        public double Add(double n1, double n2)
        {
            double result = n1 + n2;
            Console.WriteLine("Received Add({0},{1})", n1, n2);
            // Code added to write output to the console window.
            Console.WriteLine("Return: {0}", result);
            return result;
        }

        public double Subtract(double n1, double n2)
        {
            double result = n1 - n2;
            Console.WriteLine("Received Subtract({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }

        public double Multiply(double n1, double n2)
        {
            double result = n1 * n2;
            Console.WriteLine("Received Multiply({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }

        public double Divide(double n1, double n2)
        {
            double result = n1 / n2;
            Console.WriteLine("Received Divide({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }


        FileStream fs;

        [OperationContract]
        public bool PutFile(string name, string contents)
        {
            try
            {
                HttpContext context = HttpContext.Current;
                string virtPath = context.Server.MapPath(".");
                string path = virtPath + "\\" + name;
                fs = File.Open(path, FileMode.Create);
                System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
                byte[] bytes = encoding.GetBytes(contents);
                fs.Write(bytes, 0, bytes.Length);
                fs.Close();
                return true;
            }
            catch
            {
                if (fs != null)
                    fs.Close();
                return false;
            }
        }

        [OperationContract]
        public bool OpenFileForWrite(string name)
        {
            try
            {
                HttpContext context = HttpContext.Current;
                string virtPath = context.Server.MapPath(".");
                string path = virtPath + "\\App_Data\\" + name;

                fs = new FileStream(path, FileMode.Create, FileAccess.Write);
                context.Session["fileStream"] = fs;
                return true;
            }
            catch (Exception ex)
            {
                Console.Write("\n  {0}", ex.Message);
                if (fs != null)
                    fs.Close();
                return false;
            }
        }

        [OperationContract]
        public bool WriteBlock(byte[] block)
        {
            try
            {
                HttpContext context = HttpContext.Current;
                fs = (FileStream)context.Session["fileStream"];
                fs.Write(block, 0, block.Length);
                fs.Flush();
                return true;
            }
            catch
            {
                if (fs != null)
                {
                    fs.Close();
                }
                return false;
            }
        }

        [OperationContract]
        public bool CloseFile()
        {
            try
            {
                HttpContext context = HttpContext.Current;
                fs = (FileStream)context.Session["fileStream"];
                fs.Close();
                return true;
            }
            catch
            {
                if (fs != null)
                    fs.Close();
            }
            return false;
        }
    }
}
