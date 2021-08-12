import java.rmi.Remote;
import java.rmi.RemoteException;
public interface IServidor extends Remote{
  public void publicar(int revistaPublicar , int valorPublicar)throws RemoteException;
  public void assinar(ICliente cliente , int revistaAssinada ) throws RemoteException;
}
