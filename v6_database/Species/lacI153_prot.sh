file = [lacI153_prot.xml]

MoDeL
{
	species id = [lacI153_prot], name = [lacI153 protein]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[lacI153 monomer];
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
							partLabel:[lacI153];
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
			}
			listOfTrees
			{
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[dmr_lacI153_prot] speciesType = [reactant];
		}
	}
}
