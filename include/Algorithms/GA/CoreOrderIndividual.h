/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoreOrderIndividual.h
 * Author: paulofilho
 *
 * Created on 26 de fevereiro de 2019, 22:58
 */

#ifndef COREORDERINDIVIDUAL_H
#define COREORDERINDIVIDUAL_H


#include <vector>
#include <memory>
#include <iostream>

class GACoreOrder;

#include"Individual.h"

/**
 * @brief Specific individual for Core Order, composed by a genes matrix.
 */
class CoreOrderIndividual: public Individual {
public:
    /**
     * @brief Default constructor for this specified individual.
     * @param ga GACoreOrder pointer that owns this individual.
     */
    CoreOrderIndividual(GACoreOrder* ga);
    /**
     * @brief Copy constructor for this individual.
     * @param orig Original individual to be copied.
     */
    CoreOrderIndividual(const std::shared_ptr<const CoreOrderIndividual>& orig);
    /**
     * @brief Default destructor of this individual.
     */

    virtual ~CoreOrderIndividual();
    /**
     * @brief Gets the gene of  this individual,for a specified line and column, 
     * used to find the container position.
     * @param line-requisitions, used to find the container position.
     * @param column-cores, used to find the container position.
     * @return Gene, unsigned int value, of this individual.
     */
    unsigned int GetGene(unsigned int line, unsigned int column) const;
    /**
     * @brief Sets the gene of  this individual,for a specified line and column, 
     * used to set the container position.
     * @param line-requisitions, used to find the container position.
     * @param column-cores, used to find the container position.
     * @param value Gene, unsigned int value, of this individual.
     */
    void SetGene(unsigned int line, unsigned int column,unsigned int val);
    /**
     * @brief Gets the blocking probability of this individual.
     * @return Blocking probability.
     */
    double GetBlockProb() const;
    /**
     * @brief Sets the blocking probability of this individual. 
     * @param blockProb Blocking probability.
     */
    void SetBlockProb(double blockProb);
    /**
     * @brief Gets the main parameter of this individual, in this case the
     * blocking probability.
     * @return Blocking probability.
     */
    double GetMainParameter() override;    
private:

    /**
     * @brief GA_RsaOrder that owns this individual.
     */
    GACoreOrder* ga;
    /**
     * @brief Individual Genes,matrix number of lines express the number of
     * possible requisitions and the columns represent the number of cores.
     */
    std::vector<std::vector<unsigned int>> genes;
    /**
     * @brief Blocking probability of this individual.
     */
    double blockProb;

};

#endif /* COREORDERINDIVIDUAL_H */

