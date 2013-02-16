package com.suplink.entities;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.*;

@Entity
@Table(catalog = "suplink", schema = "")
@NamedQueries({
    @NamedQuery(name = "Users.login", query = "SELECT u FROM Users u WHERE u.email = :email AND u.password = :password AND u.activated = :activated "),
    @NamedQuery(name = "Users.getByID", query = "SELECT u FROM Users u WHERE u.id = :id")
})
public class Users implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id @Basic(optional = false)
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(nullable = false)
    private Integer id;
    @Basic(optional = false)
    @Column(nullable = false, length = 250)
    private String email;
    @Basic(optional = false)
    @Column(nullable = false, length = 32)
    private String password;
    @Basic(optional = false)
    @Column(nullable = false)
    private boolean activated;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "userId")
    private Collection<Links> linksCollection;

    public Users() { }
    public Users(String email, String password) {
        this.id = null; // auto incremented so we don't care
        this.email = email;
        this.password = password;
        this.activated = false;
    }

    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }

    public boolean getActivated() { return activated; }
    public void setActivated(boolean activated) { this.activated = activated; }


    public Collection<Links> getLinksCollection() { return linksCollection; }
    public void setLinksCollection(Collection<Links> linksCollection) { this.linksCollection = linksCollection; }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id : 0);
        return hash;
    }
    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Users)) {
            return false;
        }
        Users other = (Users) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }
    @Override
    public String toString() {
        return "com.suplink.entities.Users[ id=" + id + " ]";
    }
    
}
