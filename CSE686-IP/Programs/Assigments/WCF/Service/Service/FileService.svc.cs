using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Web;
using System.IO;
using System.ServiceModel.Activation;
using System.Web.Hosting;

namespace Service
{
    [ServiceContract(Namespace = "")]

    [AspNetCompatibilityRequirements(RequirementsMode
  = AspNetCompatibilityRequirementsMode.Allowed)]
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "FileService" in code, svc and config file together.
    public class FileService// : IFileService
    {
        string virtPath
        {
            get
            {
                return HttpContext.Current.Server.MapPath(".");
            }
        }

        [OperationContract]
        public double Add(double n1, double n2)
        {
            double result = n1 + n2;
            Console.WriteLine("Received Add({0},{1})", n1, n2);
            // Code added to write output to the console window.
            Console.WriteLine("Return: {0}", result);
            return result;
        }
        [OperationContract]
        public double Subtract(double n1, double n2)
        {
            double result = n1 - n2;
            Console.WriteLine("Received Subtract({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }
        [OperationContract]
        public double Multiply(double n1, double n2)
        {
            double result = n1 * n2;
            Console.WriteLine("Received Multiply({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }
        [OperationContract]
        public double Divide(double n1, double n2)
        {
            double result = n1 / n2;
            Console.WriteLine("Received Divide({0},{1})", n1, n2);
            Console.WriteLine("Return: {0}", result);
            return result;
        }


        FileStream fs
        {
            get { return (FileStream)HttpContext.Current.Session["fileStream"] as FileStream; }
            set
            {
                if (fs != null) fs.Close();
                HttpContext.Current.Session["fileStream"] = value;
            }
        }

        [OperationContract]
        public bool PutFile(string name, string contents)
        {
            try
            {
                string path = virtPath + "\\App_Data\\" + name;
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
        public string GetFile()
        {
            return "WCF Service for lab #10.";
        }

        [OperationContract]
        public bool OpenFileForWrite(string name)
        {
            try
            {
                string path = virtPath + "\\App_Data\\" + name;

                fs = new FileStream(path, FileMode.Create, FileAccess.Write);
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

        [OperationContract]
        public bool OpenFileForRead(string name)
        {
            try
            {
                string path = virtPath + "\\App_Data\\" + name;

                fs = new FileStream(path, FileMode.Open);
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
        public byte[] ReadBlock()
        {
            try
            {
                long BlockSize = 512;
                long remainder = (int)(fs.Length - fs.Position);
                if (remainder == 0)
                    return new byte[0];
                long size = Math.Min(BlockSize, remainder);
                byte[] block = new byte[size];
                fs.Read(block, 0, block.Length);

                return block;

            }
            catch (Exception ex)
            {
                if (fs != null)
                {
                    fs.Close();
                }
                return new byte[0];
            }
        }
    }
}
