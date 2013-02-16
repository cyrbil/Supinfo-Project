package com.suplink.entities;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;
import javax.persistence.*;

@Entity
@Table(catalog = "suplink", schema = "")
@NamedQueries({
    @NamedQuery(name = "Links.findAllUserLink", query = "SELECT l FROM Links l WHERE l.userId = :user"),
    @NamedQuery(name = "Links.getByID", query = "SELECT l FROM Links l WHERE l.id = :id"),
    @NamedQuery(name = "Links.isLinkOfUser", query = "SELECT l FROM Links l WHERE l.userId = :user AND l.id = :id"),
    @NamedQuery(name = "Links.doEnable", query = "UPDATE Links l SET l.enabled = TRUE WHERE l.id = :id"),
    @NamedQuery(name = "Links.doDisable", query = "UPDATE Links l SET l.enabled = FALSE WHERE l.id = :id"),
    @NamedQuery(name = "Links.doRemove", query = "DELETE FROM Links l WHERE l.id = :id")
})
public class Links implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id @Basic(optional = false)
    @Column(nullable = false, length = 12)
    private String id;
    @Basic(optional = false)
    @Column(nullable = false, length = 100)
    private String name;
    @Lob @Basic(optional = false)
    @Column(nullable = false, length = 65535)
    private String url;
    @Basic(optional = false)
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "creation_date", nullable = false)
    private Date creationDate;
    @Basic(optional = false)
    @Column(nullable = false)
    private boolean enabled;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "linkId")
    private Collection<Redirections> redirectionsCollection;
    @JoinColumn(name = "user_id", referencedColumnName = "id", nullable = false)
    @ManyToOne(optional = false)
    private Users userId;

    public Links() { }
    public Links(String id) { this.id = id; }
    public Links(String id, String name, String url, Users creator) {
        this.id = id;
        this.name = name;
        this.url = url;
        this.creationDate = new Date();
        this.enabled = true;
        this.userId = creator;
    }
    public Links(String id, String name, String url, Date creationDate, boolean enabled, Users creator) {
        this.id = id;
        this.name = name;
        this.url = url;
        this.creationDate = creationDate;
        this.enabled = enabled;
        this.userId = creator;
    }

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getUrl() { return url; }
    public void setUrl(String url) { this.url = url; }

    public Date getCreationDate() { return creationDate; }
    public void setCreationDate(Date creationDate) { this.creationDate = creationDate; }

    public boolean isEnabled() { return enabled; }
    public void setEnabled(boolean enabled) { this.enabled = enabled; }

    public Collection<Redirections> getRedirectionsCollection() { return redirectionsCollection; }
    public void setRedirectionsCollection(Collection<Redirections> redirectionsCollection) { this.redirectionsCollection = redirectionsCollection; }

    public Users getUserId() { return userId; }
    public void setUserId(Users userId) { this.userId = userId; }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }
    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Links)) {
            return false;
        }
        Links other = (Links) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }
    @Override
    public String toString() {
        return "com.suplink.entities.Links[ id=" + id + " ]";
    }
}
