/*****************************************************************************
 * osal_dlist.h
 *
 * Copyright (C) 2019 wanshijie wanshijie@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_DLIST_H_INCLUDE
#define OSAL_DLIST_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_dlist
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#if !defined(OSAL_API_H_INCLUDE)
#error "Only 'osal/osal_api.h' can be included directly."
#endif

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/**
 * This link object must be included in each user node.
 * The node's link object is used to add the node to a list.
 * A node may have multiple link objects which would allow the node to be part of
 * multiple lists simultaneously.  This link object must be initialized by assigning
 * OSAL_DLIST_LINK_INIT to it.
 *
 * @warning The structure's content MUST NOT be accessed directly.
 */
typedef struct osal_dlist_link {
    /** Next link pointer. */
    struct osal_dlist_link *nextptr;

    /** Previous link pointer. */
    struct osal_dlist_link *prevptr;
} osal_dlist_link_t;

/**
 * This is the list object.
 * User must create this list object and initialize it by assigning
 * OSAL_DLIST_LIST_INIT to it.
 *
 * @warning User MUST NOT access the contents of this structure directly.
 */
typedef struct osal_dlist {
    /** Link to list head. */
    osal_dlist_link_t *headlinkptr;
} osal_dlist_t;

/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * When a link is created it must be initialized by assigning this macro
 * to the link before it can be used.
 */
#define OSAL_DLIST_LINK_INIT                                                 \
    (osal_dlist_link_t)                                                      \
    {                                                                        \
        NULL, NULL                                                           \
    }

/**
 * When a list is created it must be initialized by assigning this macro
 * to the list before the list can be used.
 */
#define OSAL_DLIST_LIST_INIT                                                 \
    (osal_dlist_t)                                                           \
    {                                                                        \
        NULL                                                                 \
    }

/**
 * @brief Adds a link at the head of the list.
 *
 * @param[in] listptr    - The list to add to.
 *
 * @param[in] newlinkptr - The new link to add.
 */
void osal_dlist_add_head(osal_dlist_t      *listptr,
                         osal_dlist_link_t *newlinkptr);

/**
 * @brief Adds a link at the tail of the list.
 *
 * @param[in] listptr    - The list to add to.
 *
 * @param[in] newlinkptr - The new link to add.
 */
void osal_dlist_add_tail(osal_dlist_t      *listptr,
                         osal_dlist_link_t *newlinkptr);

/**
 * @brief Adds a link after currentlinkptr.
 *
 * User must ensure that currentlinkptr is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr         - The list to add to.
 *
 * @param[in] currentlinkptr  - The new link will be inserted after this link.
 *
 * @param[in] newlinkptr      - The new link to add.
 */
void osal_dlist_add_after(osal_dlist_t      *listptr,
                          osal_dlist_link_t *currentlinkptr,
                          osal_dlist_link_t *newlinkptr);

/**
 * @brief Adds a link before currentlinkptr.
 *
 * User must ensure that currentlinkptr is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr        - The list to add to.
 *
 * @param[in] currentlinkptr - The new link will be inserted before this link.
 *
 * @param[in] newlinkptr     - The new link to add.
 */
void osal_dlist_add_before(osal_dlist_t      *listptr,
                           osal_dlist_link_t *currentlinkptr,
                           osal_dlist_link_t *newlinkptr);

/**
 * @brief Removes and returns the link at the head of the list.
 *
 * @param[in] listptr - The lis to remove from.
 *
 * @return Removed link, NULL if the link is not available because the list is empty.
 */
osal_dlist_link_t *osal_dlist_del_head(osal_dlist_t *listptr);

/**
 * @brief Removes and returns the link at the tail of the list.
 *
 * @param[in] listptr - The list to remove from.
 *
 * @return Removed link, NULL if the link is not available because the list is empty.
 */
osal_dlist_link_t *osal_dlist_del_tail(osal_dlist_t *listptr);

/**
 * @brief Removes the specified link from the list.
 *
 * User must ensure that linkremoveptr is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr         - The list to remove from.
 *
 * @param[in] linkremoveptr - The link to remove.
 */
void osal_dlist_del_link(osal_dlist_t      *listptr,
                         osal_dlist_link_t *linkremoveptr);

/**
 * @brief Get the link at the head of the list without removing it from the list.
 *
 * @param[in] listptr - The list to get.
 *
 * @return  A pointer to the head link if successful. NULL if the list is empty.
 */
osal_dlist_link_t *osal_dlist_get_head(osal_dlist_t *listptr);

/**
 * @brief Get the link at the tail of the list without removing it from the list.
 *
 * @param[in] listptr - The list to get.
 *
 * @return  A pointer to the tail link if successful. NULL if the list is empty.
 */
osal_dlist_link_t *osal_dlist_get_tail(osal_dlist_t *listptr);

/**
 * @brief Get the link next to currentlinkptr.
 *
 * User must ensure that currentlinkptr is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr        - The list to get.
 *
 * @param[in] currentlinkptr - Get the link that is relative to this link.
 *
 * @return  A pointer to the next link if successful.
 *          NULL if there is no link next to the currentlinkptr(at the tail of the list).
 */
osal_dlist_link_t *osal_dlist_get_next(osal_dlist_t      *listptr,
                                       osal_dlist_link_t *currentlinkptr);

/**
 * @brief Get the link previous to currentlinkptr.
 *
 * User must ensure that currentlinkptr is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr        - The list to get.
 *
 * @param[in] currentlinkptr - Get the link that is relative to this link.
 *
 * @return  A pointer to the next link if successful.
 *          NULL if there is no link previous to the currentlinkptr(at the head of the list).
 */
osal_dlist_link_t *osal_dlist_get_prev(osal_dlist_t      *listptr,
                                       osal_dlist_link_t *currentlinkptr);

/**
 * @brief Swaps the position of two links in the list.
 *
 * User must ensure that both links is in the list otherwise the behaviour
 * of this function is undefined.
 *
 * @param[in] listptr      - The list to swap.
 *
 * @param[in] linkptr      - One of the two link pointers to swap.
 *
 * @param[in] otherlinkptr - Other link pointer to swap.
 */
void osal_dlist_swap(osal_dlist_t      *listptr,
                     osal_dlist_link_t *linkptr,
                     osal_dlist_link_t *otherlinkptr);

/**
 * @brief Checks if a list is empty.
 *
 * @param[in] listptr - The list to check.
 *
 * @return  true if empty, false if not.
 */
static __INLINE bool osal_dlist_is_empty(osal_dlist_t *listptr)
{
    return (osal_dlist_get_head(listptr) == NULL);
}

/**
 * @brief Checks if a link is in the list.
 *
 * @param[in] listptr - The list to check.
 *
 * @param[in] linkptr - Check if this link is in the list.
 *
 * @return  true if the link is in the list, false if not.
 */
bool osal_dlist_is_inlist(osal_dlist_t *listptr, osal_dlist_link_t *linkptr);

/**
 * @brief Checks if a link is at the head of the list.
 *
 * @param[in] listptr - The list to check.
 *
 * @param[in] linkptr - Check if this link is at the head of the list.
 *
 * @return  true if the link is at the head of the list, false if not.
 */
static __INLINE bool osal_dlist_is_head(osal_dlist_t      *listptr,
                                        osal_dlist_link_t *linkptr)
{
    return (osal_dlist_get_head(listptr) == linkptr);
}

/**
 * @brief Checks if a link is at the tail of the list.
 *
 * @param[in] listptr - The list to check.
 *
 * @param[in] linkptr - Check if this link is at the tail of the list.
 *
 * @return  true if the link is at the tail of the list, false if not.
 */
static __INLINE bool osal_dlist_is_tail(osal_dlist_t      *listptr,
                                        osal_dlist_link_t *linkptr)
{
    return (osal_dlist_get_tail(listptr) == linkptr);
}

/**
 * @brief Checks if the list is corrupted.
 *
 * @param[in] listptr - The list to check.
 *
 * @return  true if the list is corrupted, false if not.
 */
bool osal_dlist_is_corrupted(osal_dlist_t *listptr);

/**
 * @brief Get the number of links in a list.
 *
 * @param[in] listptr The list to count.
 *
 * @return  Number of links.
 */
size_t osal_dlist_numlinks(osal_dlist_t *listptr);

/**
 * Simple iteration through a doubly linked list
 */
#define OSAL_DLIST_FOREACH(listptr, iteratorptr, type, member)               \
    for ((iteratorptr) =                                                     \
             OSAL_CONTAINER_OF(osal_dlist_get_head(listptr), type, member);  \
         &((iteratorptr)->member);                                           \
         (iteratorptr) = OSAL_CONTAINER_OF(                                  \
             osal_dlist_get_next((listptr), &((iteratorptr)->member)),       \
             type,                                                           \
             member))

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_dlist)
 */
/****************************************************************************/
#endif /* OSAL_DLIST_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
