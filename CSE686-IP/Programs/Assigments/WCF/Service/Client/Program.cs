using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("\n  Demonstrating FileService hosted by Web Server");
            Console.Write("\n ================================================\n");

            Ider.FileServiceClient service
              = new Ider.FileServiceClient();
            string fileName;

            #region upload text
            Console.Write("\n  Using FileService to upload text file as single string");
            Console.Write("\n --------------------------------------------------------");

            fileName = "HelloWorld.txt";
            string content = "Hello from Ider to MCF world!";

            if (service.PutFile(fileName, content))
                Console.Write("\n  upload succeeded\n");
            else
                Console.Write("\n  upload failed\n");

            #endregion

            #region upload binary
            Console.Write("\n  Using FileService to upload binary file in blocks");
            Console.Write("\n ---------------------------------------------------");

            fileName = "app.config";

            if (service.OpenFileForWrite(fileName))
            {
                Console.Write("\n  opening source file for reading and destination for writing");
                FileStream fs = null;
                try
                {
                    fs = File.Open("../../" + fileName, FileMode.Open);
                    int bytesRead;
                    int count = 0;
                    while (true)
                    {
                        long BlockSize = 512;
                        long remainder = (int)(fs.Length - fs.Position);
                        if (remainder == 0)
                            break;
                        long size = Math.Min(BlockSize, remainder);
                        byte[] block = new byte[size];
                        bytesRead = fs.Read(block, 0, block.Length);
                        //Console.Write("\n  {0}", ASCIIEncoding.ASCII.GetString(block));
                        Console.Write("\n  writting block #{0} of {1} bytes", ++count, size);
                        service.WriteBlock(block);
                    }
                    Console.Write("\n  closing source and destination files\n\n");
                    fs.Close();
                }
                catch
                {
                    Console.Write("\n  File handling error\n\n");
                    if (fs != null)
                        fs.Close();
                    return;
                }

            }

            service.CloseFile();

            #endregion

            #region download text

            Console.Write("\n  Using FileService to download text file as single string");
            Console.Write("\n --------------------------------------------------------\n");

            Console.WriteLine(service.GetFile());
            Console.WriteLine("\n  download succeeded\n");
            #endregion

            #region download binary
            Console.Write("\n  Using FileService to download binary file");
            Console.Write("\n ---------------------------------------------------");
            fileName = "Pr3s11.doc";
            if (service.OpenFileForRead(fileName))
            {
                byte[] block;
                FileStream fs = null;
                Console.Write("\n\nDownloading...\n\n");
                int count = 0;
                try
                {
                    fs = File.Open(fileName, FileMode.Create, FileAccess.Write);

                    while ((block = service.ReadBlock()).Length > 0)
                    {
                        fs.Write(block, 0, block.Length);
                        fs.Flush();
                        //Console.Write("\n  downloaded block #{0} of {1} bytes", ++count, block.Length);

                    }

                    fs.Close();
                    Console.Write("\n  File downloaded successfully\n\n");

                }
                catch (Exception ex)
                {
                    Console.Write("\n  File handling error\n\n");
                    if (fs != null)
                        fs.Close();
                    return;
                }
            }

            service.CloseFile();

            #endregion

            service.Close();
            Console.Write("Press any key to close");
            Console.ReadKey();
        }
    }
}
