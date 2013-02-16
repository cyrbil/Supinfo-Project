package com.suplink.dao;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import javax.persistence.RollbackException;

public class SuplinkDAO {
    // this string must be RANDOM and SECRET !
    private static final String SECURE_SALT = "b52837a5c2c4dc5d12c87697af27e6e2";
    
    private final String PERSISTENCE_UNIT = "SupLinkPUMysql";
    private static SuplinkDAO instance;
    
    private EntityManagerFactory entityManagerFactory;
    private EntityManager entityManager;
    private EntityTransaction entityTransaction;
    
    static {
        try {
            instance = new SuplinkDAO();
        } catch (Exception ex) {
            Logger.getLogger(SuplinkDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static EntityManager getEntityManager()  throws Exception {
        begin();
        return instance.entityManager;
    }
    public static EntityTransaction getEntityTransaction() {
        return instance.entityTransaction;
    }
    
    public static void begin() throws Exception {
        instance.entityTransaction = instance.entityManager.getTransaction();
        if(!instance.entityTransaction.isActive())
            instance.entityTransaction.begin();
    }
    
    public static void commit() throws Exception {
        try {
            instance.entityTransaction.commit();
        } catch (RollbackException e) {
            if(instance.entityTransaction.isActive()) 
                instance.entityTransaction.rollback();
            throw e;
        }
    }
    
    public SuplinkDAO() {
        try {
            if(instance == null) {
                entityManagerFactory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT);
                entityManager = entityManagerFactory.createEntityManager();
            }
        } catch (Exception ex) {
            Logger.getLogger(SuplinkDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void _finalize() {
        try {
            instance.finalize(); // force grabage collect
        } catch (Throwable ex) {
            Logger.getLogger(SuplinkDAO.class.getName()).log(Level.FINE, null, ex);
        }
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            entityTransaction.commit(); // last commit
        } catch (Exception ex) { } // die silently mother fucka
        finally {
            try {
                if(entityTransaction != null && entityTransaction.isActive()) { entityTransaction.rollback(); }
            }  catch (Exception ex) { } // die silently mother fucka
            finally {
                try {
                    if(entityManager != null && entityManager.isOpen()) { entityManager.close(); }
                } catch (Exception ex) { } // die silently mother fucka
                finally {
                    try {
                        if(entityManagerFactory != null && entityManagerFactory.isOpen()) {  entityManagerFactory.close(); }
                    }  catch (Exception ex) { } // die silently mother fucka
                }
            }
        }
        super.finalize(); // rest is garbage collector job
    }
    
    
    public static String MD5Hash(String data) {
        try {
            MessageDigest m = MessageDigest.getInstance("MD5");
            m.reset();
            m.update((SECURE_SALT + data).getBytes("UTF-8"));
            byte[] digest = m.digest();
            BigInteger bigInt = new BigInteger(1,digest);
            String hashtext = bigInt.toString(16);
            // Now we need to zero pad it if you actually want the full 32 chars.
            while(hashtext.length() < 32 ){
              hashtext = "0"+hashtext;
            }
            return hashtext;
        } catch (Exception ex) {
            return null;
        }
    }
}
