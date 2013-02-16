package com.suplink.dao;

import com.suplink.entities.Users;
import javax.persistence.NoResultException;
import javax.persistence.TypedQuery;

public abstract class UsersDAO extends SuplinkDAO {

    public static Users create(String mail, String password) throws Exception {
        // hash password with mail, so identique password aren't the same hash
        // in database. Security Bitches !
        Users user = new Users(mail, MD5Hash(mail+password));
        getEntityManager().persist(user);
        commit();
        return user;
    }
    
    public static void delete(Users user) throws Exception {
        getEntityManager().remove(user);
        commit();
    }

    public static Users exist(String mail, String password, boolean activated) throws Exception {
        TypedQuery<Users> query;
        Users user;
        try {
            query = (TypedQuery<Users>) getEntityManager().createNamedQuery("Users.login");
            query.setParameter("email", mail);
            query.setParameter("password", MD5Hash(mail+password));
            query.setParameter("activated", activated);

            user = query.getSingleResult();
        } catch(NoResultException ex) { // no user found ...
            return null;
        }
        return user;
    }

    public static Users getUserByID(Integer id) {
        TypedQuery<Users> query;
        try {
            query = (TypedQuery<Users>) getEntityManager().createNamedQuery("Users.getByID");
            query.setParameter("id", id);
            return query.getSingleResult(); // if no result an excpetion is fired
        } catch(Exception e) {
            // silent catch of no row exception (and more)
            return null;
        }
    }
    
    public static void activateUser(Users user) throws Exception {
        user.setActivated(true);
        getEntityManager().merge(user);
        commit();
    }
}
