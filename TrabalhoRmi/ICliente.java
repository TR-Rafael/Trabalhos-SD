import java.rmi.Remote;
import java.rmi.RemoteException;
public interface ICliente extends Remote{
  public void receberConteudo(int conteudo)throws RemoteException;
  public int getRevistaAssinada()throws RemoteException;
  public String getName() throws RemoteException;
}
