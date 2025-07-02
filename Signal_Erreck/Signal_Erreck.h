/**
 * @author Luong Huu Phuc
 * @date 2025/06/21
 * @file Cac ham danh gia chat luong tin hieu 
 */

#ifndef __SIGNAL_ERRECK_H_
#define __SIGNAL_ERRECK_H_

#pragma once 

#ifdef __cplusplus
extern "C"{
#endif 

#include <stdio.h>

/**
 * @brief Root Mean Square Error (RMSE) - sai so trung binh binh phuong 
 * \brief - Dung de danh gia muc do sai lech trung binh giua tin hieu goc va sau khi xu ly
 * \brief - Dung de danh gia muc nhieu da duoc loai bo hieu qua hay khong 
 * 
 * @note - RMSE = 0, Hai tin hieu giong nhau hoan toan
 * \note - RMSE lon, tin hieu da bi sai lech nhieu so voi tin hieu goc
 * \note - La can bac hai cua MSE
 * \note - Don vi giong voi du lieu goc
 * 
 * @return Sai so tuyet doi
 * 
 * @param N So luong mau trong moi day tin hieu `x` va `y` 
 * @param x Day gia tri goc (chuan)
 * @param y Day gia tri can danh gia (sau khi da loc)
 */
double __attribute__((unused))rmse(int N, double *x, double *y);

/**
 * @brief Sai so binh phuong trung binh (Mean Squared Error)
 * 
 * @note Khac voi rmse moi cai la rmse co can bac hai
 * \note Don vi binh phuong 
 * 
 * @param N So luong mau 
 * @param X Tin hieu goc 
 * @param Y Tin hieu da xu ly 
 * @return Gia tri MSE
 */
double __attribute__((unused))mse(int N, double *X, double *Y);

/**
 * @brief He so tuong quan (Correlation Coefficient) - Danh gia muc do tuong quan tuyen tinh giua 2 tin hieu 
 * \brief - Dung de danh gia muc do giong nhau ve hinh dang, xem song sau khi xu ly co giu duoc hay khong, 
 * khong quan trong do lon tuyet doi
 *
 * @note Nam trong khoang `[-1, 1]`
 * \note - 1: Tuong quan tuyet doi duong (giong het ve hinh dang, khac bien do)
 * \note - 0: Khong tuong quan
 * \note - -1: Tuong quan tuyet doi am (doi xung nguoc lai)
 *  
 * @param N So luong mau trong moi day tin hieu `x` va `y` 
 * @param x Day gia tri goc (chuan)
 * @param y Day gia tri can danh gia (sau khi da loc)
 */
double __attribute__((unused))corrcoef(int N, double *x, double *y);

/**
 * @brief Ham tinh gia tri tuyet doi lon nhat cua 2 tin hieu goc va tin hieu ban dau (MAX ERROR)
 * \brief - Cho biet tin hieu phuc hoi `reconstructed` chenh lech bao nhieu so voi tin hieu goc 
 * \brief - No tra ve gia tri sai khac lon nhat giua hai tin hieu, tuc la loi lon nhat xay ra tai 1 diem bat ky 
 * 
 * @return - Neu `absmax()` rat nho - Tin hieu duoc khoi phuc lai rat chinh xac
 * \return - Neu `absmax()` lon - co loi tinh toan, muc do phan ra khong du 
 */
double __attribute__((unused))absmax(double *arr, int N);

/**
 * @brief Sai so tuyet doi trung binh (Mean Absolute Error) giua tin hieu goc va tin hieu da xu ly 
 * 
 * @note MAE cang nho thi 2 tin hieu cang giong nhau
 * 
 * @param N So luong mau dau vao
 * @param X Tin hieu goc
 * @param Y Tin hieu da xu ly 
 * 
 * @return double sai so MAE  
 */
double __attribute__((unused))mae(int N, double *X, double *Y);

/**
 * @brief Tinh ti so tin hieu tren nhieu (Signal-to-Noise)
 * 
 * @note Dung de danh gia muc do cai thien tin hieu sau khi loc nhieu 
 * \note SNR cao - Chat luong phuc hoi tot
 * 
 * @param N so luong mau 
 * @param original Tin hieu goc 
 * @param processed Tin hieu da xu ly
 * @return Gia tri SNR tinh theo dB 
 */
double __attribute__((unused))snr(int N, double *original, double *processed);

/**
 * @brief Ti so dinh tin hieu tren nhieu (Peak SNR), thuong dung trong anh va am thanh
 * 
 * @param N So luong mau 
 * @param original Tin hieu goc
 * @param processed Tin hieu da xu ly
 * @return double PSNR(dB)
 */
double __attribute__((unused))psnr(int N, double *original, double *processed);


/**
 * @brief Ham de tinh thoi gian thuc thi ham 
 * @return `time(ms)` - thoi gian chay cua ham
 * @note Goi truoc va sau khi ham chay 
 */
double __attribute__((unused))process_count_ms();

#ifdef __cplusplus
}
#endif

#endif //__SIGNAL_ERRECK_H_