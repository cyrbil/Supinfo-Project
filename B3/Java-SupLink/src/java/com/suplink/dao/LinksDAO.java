package com.suplink.dao;

import com.suplink.entities.Links;
import com.suplink.entities.Redirections;
import com.suplink.entities.Users;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.persistence.Query;
import javax.persistence.TypedQuery;

public abstract class LinksDAO extends SuplinkDAO {
    
    
    public static Links create(String name, String id, String url, Users creator) throws Exception {
        Links link = new Links(id, name, url, creator);
        getEntityManager().persist(link);
        commit();
        return link;
    }
    
    public static void delete(Links link) throws Exception {
        getEntityManager().remove(link);
        commit();
    }
    
    public static List<Links> getAllUserLink(Users user) {
        TypedQuery<Links> query;
        try {
            query = (TypedQuery<Links>) getEntityManager().createNamedQuery("Links.findAllUserLink");
            query.setParameter("user", user);
            return query.getResultList();
        } catch (Exception e) {
            return null;
        }
    }

    public static boolean isUserLink(String linkId, Users user) {
        boolean isUserLink = false;
        TypedQuery<Links> query;
        try {
            query = (TypedQuery<Links>) getEntityManager().createNamedQuery("Links.isLinkOfUser");
            query.setParameter("id", linkId);
            query.setParameter("user", user);
            query.getSingleResult(); // if no result an excpetion is fired
            isUserLink = true; // so we don't need to look what was returned
        } catch(Exception e) {
            // silent catch of no row exception (and more)
        }
        return isUserLink;
    }

    public static Links getLinkByID(String linkId) {
        TypedQuery<Links> query;
        try {
            query = (TypedQuery<Links>) getEntityManager().createNamedQuery("Links.getByID");
            query.setParameter("id", linkId);
            return query.getSingleResult(); // if no result an excpetion is fired
        } catch(Exception e) {
            // silent catch of no row exception (and more)
            return null;
        }
    }
    
    public static void doEnable(Links link) throws Exception {
        link.setEnabled(true);
        getEntityManager().merge(link);
        commit();
    }

    public static void doDisable(Links link) throws Exception {
        link.setEnabled(false);
        getEntityManager().merge(link);
        commit();
    }

    public static Redirections addRedirectionInfo(Links link, String o3Country, String referrer) throws Exception {
        Redirections r = new Redirections(o3Country, referrer, link);
        getEntityManager().persist(r);
        commit();
        return r;
    }
    public static Redirections addRedirectionInfo(Links link, String country, String referrer, Date date) throws Exception {
        Redirections r = new Redirections(country, referrer, link);
        r.setCreationDate(date);
        getEntityManager().persist(r);
        commit();
        return r;
    }

    public static Map<String, Integer> getClicksByDays(Links link) {
        try {
            // since we use raw mysql fonctions, we need a native query.
            Query query = getEntityManager().createNativeQuery(
                "SELECT DATE(`creation_date`) 'day', count(`id`) 'clicks'" +
                "FROM `redirections` " +
                "WHERE `link_id` = '" + link.getId() + "' " +
                "GROUP BY DATE(`creation_date`) " +
                "ORDER BY `creation_date` DESC;"
            );
            
            List<Object[]> results = query.getResultList();
            Map<String, Integer> formattedResults = new HashMap<String, Integer>();
            for (Object[] result : results) {
                formattedResults.put(result[0].toString(), Integer.parseInt(result[1].toString()));
            }
            return formattedResults;
        } catch (Exception e) {
            return null;
        }
    }

    public static Map<String, Integer> getClicksByReferrers(Links link) {
        try {
            // since we use raw mysql fonctions, we need a native query.
            Query query = getEntityManager().createNativeQuery(
                "SELECT  `referrer` , COUNT(  `id` )  'clicks'" +
                "FROM  `redirections`" +
                "WHERE  `link_id` =  '" + link.getId() + "'" +
                "GROUP BY  `referrer`" +
                "ORDER BY  `creation_date` DESC"
            );
            
            List<Object[]> results = query.getResultList();
            Map<String, Integer> formattedResults = new HashMap<String, Integer>();
            for (Object[] result : results) {
                formattedResults.put(result[0].toString(), Integer.parseInt(result[1].toString()));
            }
            return formattedResults;
        } catch (Exception e) {
            return null;
        }
    }

    public static Map<String, Integer> getClicksByCountries(Links link) {
        try {
            // since we use raw mysql fonctions, we need a native query.
            Query query = getEntityManager().createNativeQuery(
                "SELECT  `country` , COUNT(  `id` )  'clicks'" +
                "FROM  `redirections`" +
                "WHERE  `link_id` =  '" + link.getId() + "'" +
                "GROUP BY  `country`" +
                "ORDER BY  `creation_date` DESC"
            );
            
            List<Object[]> results = query.getResultList();
            Map<String, Integer> formattedResults = new HashMap<String, Integer>();
            for (Object[] result : results) {
                formattedResults.put(result[0].toString(), Integer.parseInt(result[1].toString()));
            }
            return formattedResults;
        } catch (Exception e) {
            return null;
        }
    }
}
