//
// Created by tsofi on 12/06/2019.
//

#include "library2.h"
#include "Schedule2.h"
#include "Wet2Exceptions.h"
using namespace Wet2Utils;

/* Required Interface for the Data Structure
 * -----------------------------------------*/

/* Description:   Initiates the data structure.
 * Input:         DS - A pointer to the data structure.
 *                n - The number of courses in the DS.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void *Init(int n) {
    try {
        Schedule2 *DS = new Schedule2(n);
        return (void *) DS;

    }
    catch (const Wet2Exceptions &e) {
        return NULL;
    }
    catch (std::bad_alloc &ba) {
        return NULL;
    }
}

/* Description:   Adds a new room.
 * Input:         DS - A pointer to the data structure.
 *                roomID - The ID of the room to add.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS == NULL, roomID <= 0
 *                FAILURE - If roomId is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType addRoom(void *DS, int roomID) {
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        ((Schedule2 *) DS)->addRoom(roomID);
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Deletes a room.
 * Input:         DS - A pointer to the data structure.
 *                roomID - The ID of the room to delete.
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS == NULL, roomID <= 0
 *                FAILURE - If roomId is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType deleteRoom(void *DS, int roomID) {
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        ((Schedule2 *) DS)->deleteRoom(roomID);
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Adds a new lecture.
 * Input:         DS - A pointer to the data structure.
 *                courseID - The ID of the course.
 *                groupID - The ID of the lecture group.
 *                roomID - The ID of the room, e.g. (Taub) 6
 *                hour - The hour when the lecture is taking place.
 *                numStudents - The amount of students registered to that group.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS == NULL, groupID < 0,
 *                                  courseID > n, courseID < 1,
 *                                  numStudents < 0, roomID <= 0,
 *                                  hour > m, hour < 1
 *                FAILURE - If there already exists a lecture of this group in the given hour
 *                          If the room isn't in the DS or there's already a lecture taking place the room
 *                              in the given hour
 *
 *                SUCCESS - Otherwise.
 */
StatusType addLecture(void *DS, int courseID, int groupID, int roomID, int hour, int numStudents) {
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        ((Schedule2 *) DS)->addLecture(courseID, groupID, roomID, hour, numStudents);
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Deletes a lecture from the DS.
 * Input:         DS - A pointer to the data structure.
 *                roomID - The ID of the room, e.g. (Taub) 6
 *                hour - The hour when the lecture is taking place.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS == NULL
 *                                if hour < 1 or hour > m.
 *                                if roomID <= 0
 *                FAILURE - If the room isn't in the DS or there's already a lecture taking place the room
 *                              in the given hour
 *                SUCCESS - Otherwise.
 */
StatusType deleteLecture(void *DS, int hour, int roomID) {
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        ((Schedule2 *) DS)->deleteLecture(hour, roomID);
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Merges the two courses.
 * Input:         DS - A pointer to the data structure.
 *                courseID1 - The id of the first course.
 * 				  courseID2 - The id of the second course.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS == NULL, or if courseID(1/2) < 1, or if courseID(1/2) > n.
 *                FAILURE - If both ID's refer to the same course, or both courses have a lecture of the same groupId at the same hour
 *                SUCCESS - Otherwise.
 */
StatusType mergeCourses(void *DS, int courseID1, int courseID2) {
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        ((Schedule2 *) DS)->mergeCourses(courseID1, courseID2);
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Conduct a competition between the two courses.
 * Input:         DS - A pointer to the data structure.
 *                courseID1 - The first course in the competition.
 * 				  courseID2 - The second course in the competition.
 * 				  numGroups - The numbers of groups each course is allowed to use.
 * Output:        winner - A pointer to a to a variable that you should contain the id of the winner course.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT -   If any of the pointers is NULL
 *                                  If DS == NULL, or if courseID(1/2) <= 0, or if courseID(1/2) > n or numGroups <= 0.
 *                FAILURE - If the two ID's refer to the same course.
 *                SUCCESS - Otherwise.
 */
StatusType competition(void *DS, int courseID1, int courseID2, int numGroups, int *winner){
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        *winner= ((Schedule2 *) DS)->competition(courseID1, courseID2, numGroups);
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Returns the average amount of students in each group of the corresponding course.
 * Input:         DS - A pointer to the data structure.
 *                roomID - The ID of the room, e.g. (Taub) 6
 *                hour - The hour when the lecture is taking place.
 * Output:        average - A pointer to a to a variable that you should contain the requested value.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the pointers is NULL
 *                                or if hour < 1, hour < m,
 								  or roomID <= 0
 *                FAILURE - If there's no room with that ID in DS, or no lecture
 *                          is taking place in the given hour
 *                SUCCESS - Otherwise.
 */
StatusType getAverageStudentsInCourse(void *DS, int hour, int roomID, float *average){
    if (DS == NULL)
        return INVALID_INPUT;
    try {
        *average= ((Schedule2 *) DS)->getAverageStudentsInCourse(hour, roomID);
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (InvalidInput &ii) {
        return INVALID_INPUT;
    } catch (Failure &f) {
        return FAILURE;
    } catch (std::exception &e) {
        return FAILURE;
    }

    return SUCCESS;
}

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit(void **DS){
    delete (((Schedule2 *) *DS));
    *DS=NULL;
}


