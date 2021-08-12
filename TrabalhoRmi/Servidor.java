import java.util.HashMap;
import java.util.Iterator;
import java.util.ArrayList;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.RMISecurityManager;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Servidor implements IServidor {
    private HashMap<Integer,ArrayList<ICliente >> assinaturas = new HashMap<Integer,ArrayList<ICliente>>();
    private HashMap<Integer,Revista> revistas  = new HashMap<Integer,Revista>();

    public void assinar(ICliente cliente , int idRevista ){

      ArrayList<ICliente> aux = assinaturas.get(idRevista);
      if(aux==null){
        aux = new ArrayList<ICliente>();
      }
      aux.add(cliente);
      assinaturas.put(idRevista,aux);
    }

    public void publicar(int revistaPublicar , int valorPublicar){

      Revista r = revistas.get(revistaPublicar);
      r.setConteudo(valorPublicar);
      ArrayList<ICliente> cAux = assinaturas.get(revistaPublicar);
      for(ICliente cliente : cAux){
        try{
          Registry registry = LocateRegistry.getRegistry();
          ICliente stub = (ICliente) registry.lookup(cliente.getName());
          stub.receberConteudo(r.getConteudo());
        }catch (Exception e){
          e.printStackTrace();
        }
    }
  }
  public void criarRevista(int id){
    Revista revista = new Revista(id);
    revistas.put(id,revista);
    assinaturas.put(id,null);
  }
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Servidor serv = new Servidor();
   try{
     IServidor stub = (IServidor)UnicastRemoteObject.exportObject(serv,0);
     Registry rg = LocateRegistry.getRegistry();
     rg.bind("Servidor",stub);
     System.out.println("Servidor Pronto");
   }catch(Exception e){}
  int escolha = 0 ;
  do{
    System.out.println("1 - Criar uma nova revista ");
    System.out.println("2 - Sair ");
    escolha = sc.nextInt();
    switch(escolha){
      case 1:
        System.out.println("Digite o id da revista ");
        int id = sc.nextInt();
        serv.criarRevista(id);
    }
  }while(escolha!=2);

 }
}
