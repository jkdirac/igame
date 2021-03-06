file = [E_coli.xml]

MoDeL
{
	part
	{
		compartment id = [E_coli], name = [Escherichia coli]
		{
			interface
			{
				url:[http://en.wikipedia.org/wiki/Escherichia_coli];
				shortDesc:[a Gram negative rod-shaped bacterium that is commonly found in the lower intestine of warm-blooded organisms (endotherms)];
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [growthRate], name = [growth rate of cell], commonValue = [5.766E-4], units = [per_second]
				{
				}
				conditionalParameter id = [maxConcentration], name = [max concentration of cell], commonValue = [1.66E-12], units = [per_second]
				{
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[E_coli_cell] partType = [Compartment];
			}
		}
	}
}
