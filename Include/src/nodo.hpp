class nodo {
  public:
    nodo() {};
    nodo(int id) : id_(id) {}
    
    bool operator==(const nodo& other) const {
      return this->id_ == other.id_;
    }

    bool operator<(const nodo& other) const {
      return this->id_ < other.id_;
    }

    int getID() const {
      return id_;
    }

    void setPadre(nodo* padre) {padre_ = padre;}
    nodo* getPadre() const {return padre_;}
    int getCosteRama() {return coste_rama_nodo;} 
    void setCosteRama(int coste) {coste_rama_nodo = coste;}

  private:
    int id_;
    nodo* padre_;
    int coste_rama_nodo = 0;
};