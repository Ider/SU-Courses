using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Service
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IFileService" in both code and config file together.
    [ServiceContract(Namespace = "http://www.cbblogs.com/ider")]
    interface IFileService
    {
        [OperationContract]
        double Add(double n1, double n2);
        [OperationContract]
        double Subtract(double n1, double n2);
        [OperationContract]
        double Multiply(double n1, double n2);
        [OperationContract]
        double Divide(double n1, double n2);


        [OperationContract]
        bool PutFile(string name, string contents);
        [OperationContract]
        bool OpenFileForWrite(string name);
        [OperationContract]
        bool WriteBlock(byte[] block);
        [OperationContract]
        bool CloseFile();

    }
}
