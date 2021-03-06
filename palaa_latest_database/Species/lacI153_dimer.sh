file = [lacI153_dimer.xml]

MoDeL
{
	species id = [lacI153_dimer], name = [lacI153 dimer]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[lacI153 dimer];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X0];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_0];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X1];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X2];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_1];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X3];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
			}
			listOfTrees
			{
				tree
				{
					listOfNodes
					{
						node
						{
							currentNodeLabel:[lacI_0];
							parentNodeLabel:[lacI2_0];
						}
						node
						{
							currentNodeLabel:[lacI_1];
							parentNodeLabel:[lacI2_0];
						}
						node
						{
							currentNodeLabel:[lacI2_0];
							parentNodeLabel:[ROOT];
						}
					}
				}
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[dmr_lacI153_2] speciesType = [reactant];
		}
	}
}
