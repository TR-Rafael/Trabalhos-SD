import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Random;

public class Cliente implements ICliente{
  private String nome;
  private int revistaAssinada ;
  public Cliente(String nome , int revistaAssinada){
    this.nome = nome;
    this.revistaAssinada = revistaAssinada ;
  }
  public void receberConteudo(int conteudo){
    System.out.println("Novo conteudo publicado : " + conteudo);
  }
  public int getRevistaAssinada(){
    return this.revistaAssinada;
  }
  public String getName(){
    return this.nome;
  }
  public static void main(String[] args) {
    Random rand = new Random();
    if(args.length == 3 ){
      System.out.println("Assinando revista: "+ args[1] + " Publicando revista : "+ args[2]);
      int revistaPublicar = Integer.parseInt(args[2]);
      ICliente c = new Cliente(args[0],Integer.parseInt(args[1]));
      try{
        ICliente stubCliente = (ICliente)UnicastRemoteObject.exportObject(c,0);
        Registry rg = LocateRegistry.getRegistry();
        rg.bind(c.getName(), stubCliente);

        rg = LocateRegistry.getRegistry();
        IServidor stub = (IServidor) rg.lookup("Servidor");

        stub.assinar(c,c.getRevistaAssinada());
        stub.publicar(revistaPublicar,rand.nextInt(10000));
      }catch(Exception e){}
    }
    else{
      System.out.println("Argumentos invalidos! Use -> [nomeCliente] [revistaAssinar] [revistaPublicar]");
    }
  }
}
