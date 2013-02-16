package com.suplink.entities;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.*;


@Entity
@Table(catalog = "suplink", schema = "")
public class Redirections implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(nullable = false)
    private Integer id;
    @Basic(optional = false)
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="creation_date", nullable = false)
    private Date creationDate;
    @Lob @Column(length = 65535)
    private String referrer;
    @Basic(optional = false)
    @Column(nullable = false, length = 3)
    private String country;
    @JoinColumn(name = "link_id", referencedColumnName = "id", nullable = false)
    @ManyToOne(fetch= FetchType.LAZY, optional = false)
    private Links linkId;

    public Redirections() { }
    public Redirections(Integer id) { this.id = id; }
    public Redirections(String country, String referrer, Links link) {
        this.country = country;
        this.referrer = referrer;
        this.linkId = link;
    }
    public Redirections(Integer id, Date date, String country, String referrer) {
        this.id = id;
        this.creationDate = date;
        this.country = country;
        this.referrer = referrer;
    }

    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }

    public Date getCreationDate() { return creationDate; }
    public void setCreationDate(Date date) { this.creationDate = date; }

    public String getReferrer() { return referrer; }
    public void setReferrer(String referrer) { this.referrer = referrer; }

    public String getCountry() { return country; }
    public void setCountry(String country) { this.country = country; }

    public Links getLinkId() { return linkId; }
    public void setLinkId(Links linkId) { this.linkId = linkId; }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id : 0);
        return hash;
    }
    @Override
    public boolean equals(Object object) {
        if (!(object instanceof Redirections)) {
            return false;
        }
        Redirections other = (Redirections) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }
    @Override
    public String toString() {
        return "com.suplink.entities.Redirections[ id=" + id + " ]";
    }
}