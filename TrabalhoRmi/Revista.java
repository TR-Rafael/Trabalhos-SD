public class Revista {
  private int id;
  private int conteudo= 0;
  public Revista(int id){
    this.id = id ; 
  };
  public void setConteudo(int conteudo){
    this.conteudo = conteudo;
  }
  public int getConteudo(){
    return this.conteudo;
  }
}
